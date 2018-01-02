module timer(TimerInterrupt, TimerAddress, cycle,
             address, data, MemRead, MemWrite, clock, reset);
    output        TimerInterrupt, TimerAddress;
    output [31:0] cycle;
    input  [31:0] address, data;
    input         MemRead, MemWrite, clock, reset;
    wire   [31:0] cycle_out, alu_out, one, interrupt_out;
    wire          interrupt_line_enable, interrupt_line_reset, ad1c, ad6c, TimerRead, TimerWrite, Acknowledge;

    // complete the timer circuit here

    // HINT: make your interrupt cycle register reset to 32'hffffffff
    //       (using the reset_value parameter)
    //       to prevent an interrupt being raised the very first cycle
    assign one = 32'b1;
    assign interrupt_line_enable = (cycle_out == interrupt_out);
    assign ad1c = (address == 32'hffff001c);
    assign ad6c = (address == 32'hffff006c);

    register reg_cycle_counter(cycle_out, alu_out, clock, 1'd1, reset);
    register #(32, 32'hffffffff) register_interrupt_cycle(interrupt_out, data, clock, TimerWrite, reset);
    alu32 alu(alu_out, , , `ALU_ADD, cycle_out, one);

    tristate tstate(cycle, cycle_out, TimerRead);

    dffe interrupt_line(TimerInterrupt, 1'd1, clock, interrupt_line_enable, interrupt_line_reset);

    or o1(interrupt_line_reset, Acknowledge, reset);
    or o2(TimerAddress, ad1c, ad6c);

    and a1(TimerRead, ad1c, MemRead);
    and a2(TimerWrite, ad1c, MemWrite);
    and a3(Acknowledge, ad6c, MemWrite);
endmodule
