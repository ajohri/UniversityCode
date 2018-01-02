SHELL=/bin/bash

CC=icpc
CCFLAGS = -O3 -qopt-report=5 

SRC=*.c
TARGETS=mp0_b.exe

all: $(TARGETS)

mp0_b.exe: mp0_b.c test1.c test2.c test3.c test4.c util.c timers.c
	$(CC) $(CCFLAGS) -o mp0_b.exe mp0_b.c test1.c test2.c test3.c test4.c util.c timers.c

clean:
	rm -f *.o *.optrpt $(TARGETS) 
