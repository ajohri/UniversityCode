module blackbox_test;

	reg l_in, u_in, m_in;

	wire a_out;

	blackbox test (a_out, l_in, u_in, m_in);

	initial begin

		$dumpfile("blackbox.vcd");
		$dumpvars(0,blackbox_test);

		l_in = 0; u_in = 0; m_in = 0; # 10;
		l_in = 0; u_in = 0; m_in = 1; # 10;
		l_in = 0; u_in = 1; m_in = 0; # 10;
		l_in = 0; u_in = 1; m_in = 1; # 10;
		l_in = 1; u_in = 0; m_in = 0; # 10;
		l_in = 1; u_in = 0; m_in = 1; # 10;
		l_in = 1; u_in = 1; m_in = 0; # 10;
		l_in = 1; u_in = 1; m_in = 1; # 10;

		$finish;
	end

	initial
		$monitor("At time %2t, l_in = %d u_in = %d m_in = %d a_out = %d", $time, l_in, u_in, m_in, a_out);
endmodule // blackbox_test
