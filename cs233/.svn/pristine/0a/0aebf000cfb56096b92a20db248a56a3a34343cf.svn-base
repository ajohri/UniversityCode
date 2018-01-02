`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 04/01/2016 01:02:31 PM
// Design Name:
// Module Name: bin2dec_tb
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


module DecimalDigitDecoder_tb(
    );

    reg [3:0] v_in;
    wire z_out;
    wire [3:0] m_out;
    integer k;
    binary2decimal U1 (.v(v_in), .z(z_out), .m(m_out));

    initial
    begin
        v_in=0;
        for(k=0; k<16; k=k+1)
            #10 v_in=k;
        #20;
    end
endmodule
