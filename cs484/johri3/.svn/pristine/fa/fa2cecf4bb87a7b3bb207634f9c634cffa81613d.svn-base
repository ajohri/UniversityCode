SHELL = /bin/bash

CC=mpicxx

OPT_LEVEL = -O0

MPICXX=$(CC) -g -O0 -std=c++11

all:  histogram_sort 

histogram_sort:  histogram_sort.cpp utils.cpp sort.h
		$(MPICXX) -o histogram_sort histogram_sort.cpp utils.cpp

clean:
	rm histogram_sort 
