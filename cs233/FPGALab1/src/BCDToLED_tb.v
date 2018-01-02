`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 03/29/2016 12:46:06 PM
// Design Name:
// Module Name: bcd2led_tb
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////


module BCDToLED_tb(
    );
    reg [3:0] x_in;
    wire [6:0] seg_out;
    wire [3:0] an_out;
    integer k;
    bcd2led U1 (.x(x_in), .seg(seg_out), .an(an_out));

    initial
    begin
        x_in=0;
        for(k=0; k<16; k=k+1)
            #10 x_in=k;
        #20;
    end

endmodule
