module illini_reader_test;

   reg reset = 1;
   reg [2:0] bits = 3'b0;
   reg clk = 0;
   always #5 clk = !clk;
   
   initial begin

      $dumpfile("illini.vcd");  
      $dumpvars(0, illini_reader_test);
      
      # 12
	reset = 0;
      # 20
	bits = 3'b111;     // I 
      # 10
	bits = 3'b000;
      # 30
      $finish;              // end the simulation
   end                      
   
   wire I, L, hyphen, N;
   illini_reader illini(I, L, hyphen, N, bits, clk, reset);

   initial
     $monitor("At time %t, bits = %b I = %d L = %d hyphen = %d N = %d reset = %x",
              $time, bits, I, L, hyphen, N, reset);
endmodule // illini_reader_test
