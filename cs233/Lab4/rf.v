// register: A register which may be reset to an arbirary value
//
// q      (output) - Current value of register
// d      (input)  - Next value of register
// clk    (input)  - Clock (positive edge-sensitive)
// enable (input)  - Load new value? (yes = 1, no = 0)
// reset  (input)  - Asynchronous reset    (reset = 1)
//
module register(q, d, clk, enable, reset);

    parameter
        width = 32,
        reset_value = 0;
 
    output [(width-1):0] q;
    reg    [(width-1):0] q;
    input  [(width-1):0] d;
    input                clk, enable, reset;
 
    always@(reset)
      if (reset == 1'b1)
        q <= reset_value;
 
    always@(posedge clk)
      if ((reset == 1'b0) && (enable == 1'b1))
        q <= d;

endmodule // register

module decoder2 (out, in, enable);
    input     in;
    input     enable;
    output [1:0] out;
 
    and a0(out[0], enable, ~in);
    and a1(out[1], enable, in);
endmodule // decoder2

module decoder4 (out, in, enable);
    input [1:0]    in;
    input     enable;
    output [3:0]   out;
    wire [1:0]    w_enable;
 
    // implement using decoder2's
    
endmodule // decoder4

module decoder8 (out, in, enable);
    input [2:0]    in;
    input     enable;
    output [7:0]   out;
    wire [1:0]    w_enable;
 
    // implement using decoder2's and decoder4's
 
endmodule // decoder8

module decoder16 (out, in, enable);
    input [3:0]    in;
    input     enable;
    output [15:0]  out;
    wire [1:0]    w_enable;
 
    // implement using decoder2's and decoder8's
 
endmodule // decoder16

module decoder32 (out, in, enable);
    input [4:0]    in;
    input     enable;
    output [31:0]  out;
    wire [1:0]    w_enable;
 
    // implement using decoder2's and decoder16's
 
endmodule // decoder32

module mips_regfile (rd1_data, rd2_data, rd1_regnum, rd2_regnum, 
             wr_regnum, wr_data, writeenable, 
             clock, reset);

    output [31:0]  rd1_data, rd2_data;
    input   [4:0]  rd1_regnum, rd2_regnum, wr_regnum;
    input  [31:0]  wr_data;
    input          writeenable, clock, reset;
 
    wire    [31:0] decout;
    wire    [31:0] regout [31:0];
 
    decoder32 d1(decout, wr_regnum, writeenable);
    register r0(regout[0], wr_data, clock, decout[0], reset);
    register r1(regout[1], wr_data, clock, decout[1], reset);
    register r2(regout[2], wr_data, clock, decout[2], reset);
    register r3(regout[3], wr_data, clock, decout[3], reset);
    register r4(regout[4], wr_data, clock, decout[4], reset);
    register r5(regout[5], wr_data, clock, decout[5], reset);
    register r6(regout[6], wr_data, clock, decout[6], reset);
    register r7(regout[7], wr_data, clock, decout[7], reset);
    register r8(regout[8], wr_data, clock, decout[8], reset);
    register r9(regout[9], wr_data, clock, decout[9], reset);
    register r10(regout[10], wr_data, clock, decout[10], reset);
    register r11(regout[11], wr_data, clock, decout[11], reset);
    register r12(regout[12], wr_data, clock, decout[12], reset);
    register r13(regout[13], wr_data, clock, decout[13], reset);
    register r14(regout[14], wr_data, clock, decout[14], reset);
    register r15(regout[15], wr_data, clock, decout[15], reset);
    register r16(regout[16], wr_data, clock, decout[16], reset);
    register r17(regout[17], wr_data, clock, decout[17], reset);
    register r18(regout[18], wr_data, clock, decout[18], reset);
    register r19(regout[19], wr_data, clock, decout[19], reset);
    register r20(regout[20], wr_data, clock, decout[20], reset);
    register r21(regout[21], wr_data, clock, decout[21], reset);
    register r22(regout[22], wr_data, clock, decout[22], reset);
    register r23(regout[23], wr_data, clock, decout[23], reset);
    register r24(regout[24], wr_data, clock, decout[24], reset);
    register r25(regout[25], wr_data, clock, decout[25], reset);
    register r26(regout[26], wr_data, clock, decout[26], reset);
    register r27(regout[27], wr_data, clock, decout[27], reset);
    register r28(regout[28], wr_data, clock, decout[28], reset);
    register r29(regout[29], wr_data, clock, decout[29], reset);
    register r30(regout[30], wr_data, clock, decout[30], reset);
    register r31(regout[31], wr_data, clock, decout[31], reset);

    mux32v m1(rd1_data, regout[0], regout[1], regout[2], regout[3], regout[4], regout[5], regout[6], regout[7], regout[8], regout[9], regout[10], regout[11], regout[12], regout[13], regout[14], regout[15], regout[16], regout[17], regout[18], regout[19], regout[20], regout[21], regout[22], regout[23], regout[24], regout[25], regout[26], regout[27], regout[28], regout[29], regout[30], regout[31], rd1_regnum);

    mux32v m2(rd2_data, regout[0], regout[1], regout[2], regout[3], regout[4], regout[5], regout[6], regout[7], regout[8], regout[9], regout[10], regout[11], regout[12], regout[13], regout[14], regout[15], regout[16], regout[17], regout[18], regout[19], regout[20], regout[21], regout[22], regout[23], regout[24], regout[25], regout[26], regout[27], regout[28], regout[29], regout[30], regout[31], rd2_regnum);
    
endmodule // mips_regfile

