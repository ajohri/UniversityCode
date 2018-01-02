module logicunit_test;
    // exhaustively test your logic unit by adapting mux4_tb.v
    reg A = 0;
    always #1 A = !A;

    reg B = 0;
    always #2 B = !B;

    reg [1:0] control = 0;

    intial begin
    	$dumpfile("logicunit.vcd");
    	$dumpcars(0, logicunit_test);

    	# 16 control = 1;
    	# 16 control = 2;
    	# 16 control = 3;
    	# 16 $finish;
    end

    wire out;
    logicunit l1(out, A, B, control);

    intial begin
    	$display("A B s o");
    	$monitor(" %d %d %d %d (at time %t)", A, B, control, out, $time);
    end
endmodule // logicunit_test
