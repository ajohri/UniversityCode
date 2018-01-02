SHELL = /bin/bash

CC=g++

OPT_LEVEL = -O0

BASIC_PERF=$(CC) -g -O0 -openmp -std=c++11 -lrt -Wno-write-strings -fpermissive

all:  list_lock.exe

list_lock.exe:  main.cpp list.cpp lock_list.cpp list.h
		$(BASIC_PERF) -o list_lock.exe main.cpp list.cpp lock_list.cpp list.h -lpthread 

clean:
	rm *.exe
