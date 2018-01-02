SHELL=/bin/bash

CC=icpc
CCFLAGS = -O2  

SRC=mp0_a.c

all: mp0_a.exe

mp0_a.exe: mp0_a.o
	$(CC) $(CCFLAGS) -o mp0_a.exe mp0_a.o

mp0_a.o: mp0_a.c
	$(CC) $(CCFLAGS) -c mp0_a.c

clean:
	rm -f *.o *.exe
