SHELL = /bin/bash

CC=g++

OPT_LEVEL = -O0

BASIC_PERF=$(CC) -g -O0 -openmp -std=c++11 -lrt -Wno-write-strings -fpermissive

all:  basic_perf.exe 

basic_perf.exe: main_basic.cpp  basic.cpp basic_unrolled.cpp basic_flipped.cpp basic_block.cpp papi_support.c papi_helpers.c 
		$(BASIC_PERF) -o basic_perf.exe  main_basic.cpp basic.cpp basic_unrolled.cpp basic_flipped.cpp basic_block.cpp papi_support.c papi_helpers.c -lm -L /usr/local/apps/papi/5.4.1/lib -lpapi 

clean:
	rm *.exe 
