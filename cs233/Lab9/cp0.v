`define STATUS_REGISTER 5'd12
`define CAUSE_REGISTER  5'd13
`define EPC_REGISTER    5'd14

module cp0(rd_data, EPC, TakenInterrupt,
           regnum, wr_data, next_pc, TimerInterrupt,
           MTC0, ERET, clock, reset);
    output [31:0] rd_data;
    output [29:0] EPC;
    output        TakenInterrupt;
    input   [4:0] regnum;
    input  [31:0] wr_data;
    input  [29:0] next_pc;
    input         TimerInterrupt, MTC0, ERET, clock, reset;
    wire    [31:0] user_status_out, status_register, cause_register, decoder_out, EPC_added2;
    wire    [29:0] EPC_data, EPC_register_out;
    wire    EPCenable, exception_reset, exception_level_out, and1, and2, nsr1;

    decoder32 decoder(decoder_out,  regnum, MTC0);

    assign status_register = {16'b0, user_status_out[15:8], 6'b0, exception_level_out, user_status_out[0]};

    assign cause_register = {16'b0, TimerInterrupt, 15'b0};

    or orgate1(EPCenable, TakenInterrupt, decoder_out[14]);
    mux2v #(30) m1(EPC_data, wr_data[31:2], next_pc, TakenInterrupt);
    register #(30) EPC_register(EPC_register_out, EPC_data, clock, EPCenable, reset);

    register user_status(user_status_out, wr_data, clock, decoder_out[12], reset);

    or orgate2(exception_reset, reset, ERET);


    dffe exception_level(exception_level_out, 1, clock, TakenInterrupt, exception_reset);

    assign EPC_added2 = {EPC_register_out[29:0], 2'b0};

    mux32v #(32) m2(rd_data, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, status_register, cause_register, EPC_added2,
        1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, 1'd0, regnum);

    assign EPC = EPC_register_out;

    and a1(and1, cause_register[15], status_register[15]);
    not nsr(nsr1, status_register[1]);
    and a2(and2, nsr1, status_register[0]);
    and a3(TakenInterrupt, and1, and2);


    // your Verilog for coprocessor 0 goes here
endmodule
