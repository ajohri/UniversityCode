module i_reader_test;
 
    reg restart = 1;
    reg [2:0] bits = 3'b0;
    reg clk = 0;
    always #5 clk = !clk;
    
    initial begin
 
        $dumpfile("i_reader.vcd");  
        $dumpvars(0, i_reader_test);
       
        # 12
          restart = 0;
        # 20
          bits = 3'b111; // start of I
        # 10
          bits = 3'b000; // I should be recognized after this
        # 10
          $finish;              // end the simulation
    end                      
    
    wire I;
    i_reader ir(I, bits, clk, restart);
 
// discouraged:  most students find this more confusing than gtkwave
//     initial
//       $monitor("At time %t, bits = %b I = %d restart = %x",
//                $time, bits, I, restart);
endmodule // i_reader_test
