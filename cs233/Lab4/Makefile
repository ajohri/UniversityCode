all: i_reader illini_reader rf
.PHONY: all clean i_reader illini_reader rf

i_reader: i_reader_exe
	./i_reader_exe

i_reader_exe: i_reader.v i_reader_tb.v 
	iverilog -o i_reader_exe -Wall i_reader.v i_reader_tb.v 

illini_reader: illini_reader_exe
	./illini_reader_exe

illini_reader_exe: illini_reader.v illini_reader_tb.v 
	iverilog -o illini_reader_exe -Wall illini_reader.v illini_reader_tb.v 

rf: rf_exe
	./rf_exe

rf_exe: rf.v rf_tb.v mux_lib.v
	iverilog -o rf_exe -Wall rf.v rf_tb.v mux_lib.v

clean:
	rm -f *_exe *.vcd
