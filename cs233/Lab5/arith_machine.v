// arith_machine: execute a series of arithmetic instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clock  (input)  - the clock signal
// reset  (input)  - set to 1 to set all registers to zero, set to 0 for normal execution.

module arith_machine(except, clock, reset);
    output      except;
    input       clock, reset;

    wire [31:0] inst;  
    wire [31:0] PC;
    wire [31:0] nextPC;
    wire [31:0] rsData;
    wire [31:0] rtData;
    wire [31:0] rdData;
    wire [31:0] imm32;
    wire [31:0] B;
    wire [4:0] Rdest;
    wire [2:0] alu_op;
    wire pc_enable, wr_enable, alu_src2, rd_src, except1, overflow, zero, negative;

    assign pc_enable = 1;  

    // DO NOT comment out or rename this module
    // or the test bench will break
    
    register #(32) PC_reg( PC, nextPC, clock, pc_enable, reset );
    alu32 pcplus4(nextPC, , , , PC, 32'h4, `ALU_ADD);

    // DO NOT comment out or rename this module
    // or the test bench will break
    
    instruction_memory im( inst, PC[31:2] );

    mips_decode md(alu_op, wr_enable, rd_src, alu_src2, except1, inst[31:26], inst[5:0]);
    assign except = except1;

    assign imm32 =  {16'h0, inst[15:0]};//{{16{inst[15]}}, inst[15:0]};            // This is the sign extender

    mux2v #(5) m2(Rdest, inst[15:11], inst[20:16], rd_src);

    // DO NOT comment out or rename this module
    // or the test bench will break
    
    regfile rf ( rsData, rtData, inst[25:21], inst[20:16], Rdest, rdData, wr_enable, clock, reset);

    mux2v #(32) m3(B, rtData, imm32, alu_src2);

    alu32 a1(rdData, overflow, zero, negative, rsData, B, alu_op);

   
endmodule // arith_machine
