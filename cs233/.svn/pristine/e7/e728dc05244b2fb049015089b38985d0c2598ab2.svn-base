// dffe: D-type flip-flop with enable
//
// q      (output) - Current value of flip flop
// d      (input)  - Next value of flip flop
// clk    (input)  - Clock (positive edge-sensitive)
// enable (input)  - Load new value? (yes = 1, no = 0)
// reset  (input)  - Asynchronous reset   (reset =  1)
//
module dffe(q, d, clk, enable, reset);
    output q;
    reg    q;
    input  d;
    input  clk, enable, reset;

    always@(reset)
      if (reset == 1'b1)
        q <= 0;

    always@(posedge clk)
      if ((reset == 1'b0) && (enable == 1'b1))
        q <= d;
endmodule // dffe


module illini_reader(I, L, hyphen, N, bits, clk, restart);
    output      I, L, hyphen, N;
    input [2:0] bits;
    input       restart, clk;
    wire        sGarbage, sGarbage_next;
    
    
    // I reader
    assign in000 = bits == 3'b000;
    assign in111 = bits == 3'b111;

    assign sGarbageI_next = ((sBlank | sI_end) & ~(in000 | in111)) | ((sI | sGarbageI) & ~in000) | restart;
    assign sBlank_next = ((sBlank | sI_end | sGarbageI) & in000) & ~restart;
    assign sI_next = ((sBlank | sI_end) & in111) & ~restart;
    assign sI_end_next = (sI & in000) & ~restart;

    // enable hardcoded to 1, reset hardcoded to 0
    dffe fsGarbageI(sGarbageI, sGarbageI_next, clk, 1'b1, 1'b0);
    dffe fsBlank(sBlank, sBlank_next, clk, 1'b1, 1'b0);
    dffe fsI(sI, sI_next, clk, 1'b1, 1'b0);
    dffe fsI_end(sI_end, sI_end_next, clk, 1'b1, 1'b0);

    // outputs are associated with states, NOT transitions
    assign I = sI_end;


    // L reader
    assign in000 = bits == 3'b000;
    assign in111 = bits == 3'b111;
    assign in001 = bits == 3'b001;

    assign sGarbage_next = (sA & ~in111) | (sA & ~in000) | (sB & ~in001) | (sB & ~in000) | (sC & ~in000) | (sD & ~in111) | (sD & ~in000) | (sGarbage & ~in000) | restart; // everything that will lead to the garbage state.
    
    assign sA_next = ((sGarbage & in000) | (sA & in000) | (sD & in000) | (sB & in000)) & ~restart; // This is the blank state
    
    assign sB_next = ((sA & in111) | (sD & in111)) & ~restart; // This is the same as the i_reader or in other words the first half of the L reader
    
    assign sC_next = (sB & in001) & ~restart; // This is the second half of the L reader
    assign sD_next = (sC & in000) & ~restart; // This is basically the blank state again but this is checking only after the letter has been made.
    
    // Definitions
    dffe fsGarbage(sGarbage, sGarbage_next, clk, 1'b1, 1'b0);
    dffe fsA(sA, sA_next, clk, 1'b1, 1'b0);
    dffe fsB(sB, sB_next, clk, 1'b1, 1'b0);
    dffe fsC(sC, sC_next, clk, 1'b1, 1'b0);
    dffe fsD(sD, sD_next, clk, 1'b1, 1'b0);

    assign L = sD;

    // Hyphen reader
    assign in000 = bits == 3'000;
    assign in010 = bits == 3'010;

    assign hGarbage_next = ((hA | hD) & ~(in000 | in010)) | ((hC | hD) & ~in010) | ((hGarbage | hE) & ~in000) | restart;
    assign hA_next = ((HGarbage & in000) | (hA & in000) | (hB & in000) | (hC & in000) | (hD & in000) | (hE & in000)); // blank state
    assign hB_next = ((hA & in010) | (hE & in010)) & ~restart;                  // first dash
    assign hC_next = ((hB & in010)) & ~restart;                                 // second dash
    assign hD_next = ((hC & in010)) & ~restart;                                 // third dash
    assign hE_next = ((hE & in000)) & ~restart;

    dffe fsGarbageH(hGarbage, hGarbage_next, clk, 1'b1, 1'b0);
    dffe fsAh(hA, hA_next, clk, 1'b1, 1'b0);
    dffe fsBh(hB, hB_next, clk, 1'b1, 1'b0);
    dffe fsCh(hC, hC_next, clk, 1'b1, 1'b0);
    dffe fsDh(hD, hD_next, clk, 1'b1, 1'b0);
    dffe fsEh(hE, hE_next, clk, 1'b1, 1'b0);

    assign hyphen = hE;

endmodule // illini_reader
