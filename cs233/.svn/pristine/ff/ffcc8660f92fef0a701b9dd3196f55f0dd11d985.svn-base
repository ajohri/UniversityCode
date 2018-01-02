// full_machine: execute a series of MIPS instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clk     (input) - the clock signal
// reset   (input) - set to 1 to set all registers to zero, set to 0 for normal execution.

module full_machine(except, clk, reset);
    output      except;
    input       clk, reset;

    wire [31:0] inst;  
    wire [31:0] PC;  
    wire [31:0] nextPC;
    wire [2:0] alu_op;
    wire [4:0] Rdest;
    wire [31:0] rsData;
    wire [31:0] rtData;
    wire [31:0] rdData;
    wire [31:0] imm32;
    wire [31:0] B;
    wire [31:0] branch_offset;
    wire [31:0] pcincrement;
    wire [31:0] brancher;
    wire [1:0] control_type;
    wire [31:0] jumper;
    wire [31:0] out;
    wire [31:0] data_out;
    wire [7:0] byteout;
    wire [31:0] ebyteout;
    wire [31:0] mem_out;
    wire [31:0] ifless;
    wire [31:0] tolui;
    wire [31:0] luiwire;
    wire [31:0] addr;
    wire [31:0] thirdalu;
    wire [31:0] prerdData;
    wire [31:0] slttrue;
    wire pcenable, wr_enable, alu_src2, rd_src, mem_read, word_we, byte_we, byte_load, lui, slt, zero, negative, addm;

    assign pcenable = 1;

    // DO NOT comment out or rename this module
    // or the test bench will break
    register #(32) PC_reg(PC, nextPC, clk, pcenable, reset);
    alu32 pcplus4(pcincrement, , , , PC, 32'h4, `ALU_ADD);
    alu32 pb(brancher, , , , pcincrement, branch_offset, `ALU_ADD);

    mux4v m10(nextPC, pcincrement, brancher, jumper, rsData, control_type);

    instruction_memory im(inst, PC[31:2]);
 
    mips_decode md(alu_op, wr_enable, rd_src, alu_src2, except, control_type,
                   mem_read, word_we, byte_we, byte_load, lui, slt, addm,
                   inst[31:26], inst[5:0], zero);

    assign jumper = {PC[31:28], inst[25:0], 2'b0};

    assign imm32 = {{16{inst[15]}}, inst[15:0]};
    assign branch_offset = {imm32[29:0], 2'b0};

    mux5bit m1(Rdest, inst[15:11], inst[20:16], rd_src);


    // DO NOT comment out or rename this module
    // or the test bench will break
    regfile rf(rsData, rtData, inst[25:21], inst[20:16], Rdest, rdData, wr_enable, clk, reset);

    mux2v m2(B, rtData, imm32, alu_src2);

    alu32 rf1(out, , zero, negative, rsData, B, alu_op);

    data_mem dm(data_out, addr, rtData, word_we, byte_we, clk, reset);
    mux4v8bit m3(byteout, data_out[7:0], data_out[15:8], data_out[23:16], data_out[31:24], out[1:0]);

    assign ebyteout = {24'b0, byteout};

    mux2v m4(mem_out, data_out, ebyteout, byte_load);

    assign ifless = {31'b0, negative};

    mux2v m5(slttrue, out, ifless, slt);
    mux2v m6(tolui, slttrue, mem_out, mem_read);

    assign luiwire = {inst[15:0], 16'b0};
    mux2v m7(prerdData, tolui, luiwire, lui);

    mux2v m8(addr, out, rsData, addm);

    alu32 addmalu(thirdalu, , , , data_out, rtData, `ALU_ADD);

    mux2v m9(rdData, prerdData, thirdalu, addm);
    /* add other modules */


endmodule // full_machine

module mux5bit(out, A, B, sel);

    parameter
        width = 5;
    
    output [width-1:0] out;
    input  [width-1:0] A, B;
    input              sel;

    wire [width-1:0] temp1 = ({width{(!sel)}} & A);
    wire [width-1:0] temp2 = ({width{(sel)}} & B);
    assign out = temp1 | temp2;

endmodule

module mux4v8bit(out, A, B, C, D, sel);

    parameter
        width = 8;
    
    output [width-1:0] out;
    input  [width-1:0] A, B, C, D;
    input  [1:0]       sel;
    wire   [width-1:0] wAB, wCD;
    
    mux2v #(width) mAB (wAB, A, B, sel[0]);
    mux2v #(width) mCD (wCD, C, D, sel[0]);
    mux2v #(width) mfinal (out, wAB, wCD, sel[1]);

endmodule // mux4v