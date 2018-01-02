module pipelined_machine(clk, reset);
   input        clk, reset;

   wire [31:0]  PC;
   wire [31:2]  next_PC, PC_plus4, PC_target, intoTargetPCAdder;
   wire [31:0]  inst, instr;

   wire [31:0]  imm = {{ 16{instr[15]} }, instr[15:0] };  // sign-extended immediate
   wire [4:0]   rs = instr[25:21];
   wire [4:0]   rt = instr[20:16];
   wire [4:0]   rd = instr[15:11];
   wire [5:0]   opcode = instr[31:26];
   wire [5:0]   funct = instr[5:0];

   wire [4:0]   wr_regnum, wr_regnumrin;
   wire [2:0]   ALUOp;

   wire         RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst, register_RegWrite, register_MemRead, register_MemWrite, register_MemToReg;
   wire         PCSrc, zero, ForwardA, ForwardB, flushing, stalling;
   wire [31:0]  rd1_data, rd2_data, B_data, alu_out_data, load_data, wr_data, ad_mem, writeDatain, ForwardB_out, ForwardA_out, wr_data_out;


   register #(30, 30'h100000) PC_reg(PC[31:2], next_PC[31:2], clk, ~stalling, reset);
   assign PC[1:0] = 2'b0;  // bottom bits hard coded to 00
   adder30 next_PC_adder(PC_plus4, PC[31:2], 30'h1);

   adder30 target_PC_adder(PC_target, intoTargetPCAdder, imm[29:0]);
   mux2v #(30) branch_mux(next_PC, PC_plus4, PC_target, PCSrc);
   assign PCSrc = BEQ & zero;

   instruction_memory imem (inst, PC[31:2]);

   mips_decode decode(ALUOp, RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst,
                      opcode, funct);

   regfile rf (rd1_data, rd2_data,
               rs, rt, wr_regnumrin, wr_data_out,
               register_RegWrite, clk, reset);

   mux2v #(32) imm_mux(B_data, rd2_data, imm, ALUSrc);
   alu32 alu(alu_out_data, zero, ALUOp, rd1_data, B_data);

   data_mem data_memory(load_data, ad_mem, writeDatain, register_MemRead, register_MemWrite, clk, reset);

   mux2v #(32) wb_mux(wr_data, alu_out_data, load_data, MemToReg);
   mux2v #(5) rd_mux(wr_regnum, rt, rd, RegDst);

   //Pipeline
   register #(30) addstuff(intoTargetPCAdder, PC_plus4, clk, ~stalling, flushing); //This is the register for the adder
   register #(32) imemr(instr, inst, clk, ~stalling, flushing); //This is the register for IF/DE from the instruction memory
   register #(1) reg_write(register_RegWrite, RegWrite, clk, 1'b1, reset | stalling);
   register #(1) mem_read(register_MemRead, MemRead, clk, 1'b1, reset | stalling);
   register #(1) mem_write(register_MemWrite, MemWrite, clk, 1'b1, reset | stalling);
   register #(1) mem_to_reg(register_MemToReg, MemToReg, clk, 1'b1, reset | stalling);
   register #(32) aluReg(ad_mem, alu_out_data, clk, 1'b1, reset | stalling);
   register #(5) wr_regnumr(wr_regnumrin, wr_regnum, clk, 1'b1, reset | stalling); //random transfer register
   register #(32) write_data(writeDatain, ForwardB_out, clk, 1'b1, reset | stalling);

   //forwarding
   assign ForwardA = (register_RegWrite & (rs == wr_regnumrin) & (wr_regnumrin != 0));
   assign ForwardB = (register_RegWrite & (rt == wr_regnumrin) & (wr_regnumrin != 0));
   mux2v #(32) forwardA_mux(ForwardA_out, rd1_data, writeDatain, ForwardA);
   mux2v #(32) forwardB_mux(ForwardB_out, rd2_data, writeDatain, ForwardB);

   assign flushing = (PCSrc || reset);

   assign stalling = register_MemRead & ((rs == wr_regnumrin) | (rt == wr_regnumrin));

   mux2v #(32) MemToReg_MW(wr_data_out, ad_mem, load_data, register_MemToReg);

endmodule // pipelined_machine
