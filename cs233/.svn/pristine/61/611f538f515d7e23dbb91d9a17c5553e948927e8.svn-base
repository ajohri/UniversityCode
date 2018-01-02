// mips_decode: a decoder for MIPS arithmetic instructions
//
// alu_op       (output) - control signal to be sent to the ALU
// writeenable  (output) - should a new value be captured by the register file
// rd_src       (output) - should the destination register be rd (0) or rt (1)
// alu_src2     (output) - should the 2nd ALU source be a register (0) or an immediate (1)
// except       (output) - set to 1 when we don't recognize an opdcode & funct combination
// control_type (output) - 00 = fallthrough, 01 = branch_target, 10 = jump_target, 11 = jump_register 
// mem_read     (output) - the register value written is coming from the memory
// word_we      (output) - we're writing a word's worth of data
// byte_we      (output) - we're only writing a byte's worth of data
// byte_load    (output) - we're doing a byte load
// lui          (output) - the instruction is a lui
// slt          (output) - the instruction is an slt
// addm         (output) - the instruction is an addm
// opcode        (input) - the opcode field from the instruction
// funct         (input) - the function field from the instruction
// zero          (input) - from the ALU
//

module mips_decode(alu_op, writeenable, rd_src, alu_src2, except, control_type,
                   mem_read, word_we, byte_we, byte_load, lui, slt, addm,
                   opcode, funct, zero);
    output [2:0] alu_op;
    output       writeenable, rd_src, alu_src2, except;
    output [1:0] control_type;
    output       mem_read, word_we, byte_we, byte_load, lui, slt, addm;
    input  [5:0] opcode, funct;
    input        zero;

    wire sub_ = (opcode == `OP_OTHER0) & (funct == `OP0_SUB); // Done with this guy
    wire add_ = (opcode == `OP_OTHER0) & (funct == `OP0_ADD); // Done with this guy
    wire and_ = (opcode == `OP_OTHER0) & (funct == `OP0_AND); // Done with this guy
    wire or_ = (opcode == `OP_OTHER0) & (funct == `OP0_OR); // Done with this guy
    wire nor_ = (opcode == `OP_OTHER0) & (funct == `OP0_NOR); // Done with this guy
    wire xor_ = (opcode == `OP_OTHER0) & (funct == `OP0_XOR); // Done with this guy
    wire jr_ = (opcode == `OP_OTHER0) & (funct == `OP0_JR);
    wire slt_ = (opcode == `OP_OTHER0) & (funct == `OP0_SLT);

    wire addi_ = (opcode == `OP_ADDI); // Done with this guy
    wire andi_ = (opcode == `OP_ANDI); // Done with this guy
    wire ori_ = (opcode == `OP_ORI); // Done with this guy
    wire xori_ = (opcode == `OP_XORI); // Done with this guy
    wire bne_ = (opcode == `OP_BNE); // Done with this guy
    wire beq_ = (opcode == `OP_BEQ); // Done with this guy
    wire lui_ = (opcode == `OP_LUI);
    wire lw_ = (opcode == `OP_LW);
    wire lbu_ = (opcode == `OP_LBU);
    wire sw_ = (opcode == `OP_SW); // Done with this guy
    wire sb_ = (opcode == `OP_SB); // Done with this guy
    wire j_ = (opcode == `OP_J);


    assign writeenable = (sub_ | add_ | and_ | or_ | nor_ | xor_ | addi_ | andi_ | ori_ | xori_ | lui_ | slt_ | lw_ | lbu_);
    assign alu_src2 = (addi_ | andi_ | ori_ | xori_ | sw_ | lw_ | lbu_| sb_);
    assign rd_src = (addi_ | andi_ | ori_ | xori_ | lui_ | lw_ | lbu_);
    assign except = ~(sub_ | add_ | and_ | or_ | nor_ | xor_ | j_ | jr_ | slt_ | addi_ | andi_ | ori_ | xori_ | bne_ | beq_ | lui_ | lw_ | lbu_ | sw_ | sb_);
    assign control_type[1] = j_ | jr_;
    assign control_tyep[0] = (beq_ & zero) | (bne_ & !zero) | jr_;
    assign mem_read = (lbu_ | lw_);
    assign word_we = sw_;
    assign byte_we = sb_;
    assign byte_load = lbu_;
    assign lui = lui_;
    assign slt = slt_;

    assign alu_op[0] = (sub_ | or_ | xor_ | ori_ | xori_ | beq_ | bne_ | slt_);
    assign alu_op[1] = (add_ | sub_ | nor_ | xor_ | addi_ | xori_ | beq_ | bne_ | slt_ | lw_ | lbu_ | sw_ | sb_);
    assign alu_op[2] = (and_ | or_ | nor_ | xor_ | andi_ | ori_ | xori_);

endmodule // mips_decode
