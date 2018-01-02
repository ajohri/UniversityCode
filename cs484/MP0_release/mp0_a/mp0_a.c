#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#define MAXSIZE 70000000
#include <cassert>

void timerTest();
double get_clock();

void initValues(int *A, int *indirection, int maxsize,int stride, int size) 
{
  int i;
  indirection[0] = stride % size;
  for (i=1; i<maxsize; i++) {
    A[i] = rand();
    indirection[i] = (indirection[i-1]+stride)%size;
  }
}

// Measures time in seconds

double get_clock()
{
        struct timeval tv;
	int ok;
	ok = gettimeofday(&tv,0);
	if(ok < 0)
	{
	   printf("gettimeofday error");
	   exit(-1);
	}
	  return (tv.tv_sec*1.0+tv.tv_usec*1.0E-6);
}
	     

int main(int argc, char**argv)
{
  double t1,t2,t3;
  int size, k, count1, stride, repetitions;
  int i;
  int * A;
  int *indirection;

  A = (int *) malloc(sizeof(int)* MAXSIZE);
  indirection = (int *) malloc(sizeof(int)* MAXSIZE);
  assert (A != NULL);
  assert (indirection != NULL);

  timerTest();

  repetitions = 1 << 27; // 2^27 or approx 100 million repetitions for each size
  stride = 1000;  // initial value of stride

  for (size = 1<<6; size < MAXSIZE; size = size*2) {
    initValues(A, indirection, MAXSIZE, stride, size);

    t1 = get_clock(); // record start timer after indirection array has been set.

    for (i = 0; i < repetitions/size; i++)
      for (count1 =0; count1 < size ; count1++) {
        A[count1] += A[ indirection[count1] ];
      }

    t2 = get_clock();
    printf("time for size = %d was: %lf. per access: %lf nanoseconds\n", 
        size, t2-t1, (1000000.0* (t2-t1)*1000.0)/repetitions); 
  }
}

// Testing function for the getclock routine.

void timerTest()
{
  double t0, times[100];
  int i;
  for (i=0; i<10; i++)
    times[i] = get_clock();
  for (i=0; i<10; i++) 
    printf("time at %d: %lf\n", i, times[i]-times[0]);
}
