// mips_decode: a decoder for MIPS arithmetic instructions
//
// alu_op      (output) - control signal to be sent to the ALU
// writeenable (output) - should a new value be captured by the register file
// rd_src      (output) - should the destination register be rd (0) or rt (1)
// alu_src2    (output) - should the 2nd ALU source be a register (0) or an immediate (1)
// except      (output) - set to 1 when the opcode/funct combination is unrecognized
// opcode      (input)  - the opcode field from the instruction
// funct       (input)  - the function field from the instruction
//

module mips_decode(alu_op, writeenable, rd_src, alu_src2, except, opcode, funct);
    output [2:0] alu_op;
    output       writeenable, rd_src, alu_src2, except;
    input  [5:0] opcode, funct;

    wire sub_ = (opcode == `OP_OTHER0) & (funct == `OP0_SUB);
    wire add_ = (opcode == `OP_OTHER0) & (funct == `OP0_ADD);
    wire and_ = (opcode == `OP_OTHER0) & (funct == `OP0_AND);
    wire or_ = (opcode == `OP_OTHER0) & (funct == `OP0_OR);
    wire nor_ = (opcode == `OP_OTHER0) & (funct == `OP0_NOR);
    wire xor_ = (opcode == `OP_OTHER0) & (funct == `OP0_XOR);

    wire addi_ = (opcode == `OP_ADDI);
    wire andi_ = (opcode == `OP_ANDI);
    wire ori_ = (opcode == `OP_ORI);
    wire xori_ = (opcode == `OP_XORI);

    assign writeenable = (sub_ | add_ | and_ | or_ | nor_ | xor_ | addi_ | andi_ | ori_ | xori_);
    assign alu_src2 = (addi_ | andi_ | ori_ | xori_);
    assign rd_src = (addi_ | andi_ | ori_ | xori_);
    assign except = ~(sub_ | add_ | and_ | or_ | nor_ | xor_ | addi_ | andi_ | ori_ | xori_);

    assign alu_op[0] = (sub_ | or_ | xor_ | ori_ | xori_);
    assign alu_op[1] = (add_ | sub_ | nor_ | xor_ | addi_ | xori_);
    assign alu_op[2] = (and_ | or_ | nor_ | xor_ | andi_ | ori_ | xori_); 

endmodule // mips_decode
