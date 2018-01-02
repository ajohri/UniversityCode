//Gauss-Seidel solver
//Solves for x in a square system of N linear equations: Ax = b
#include "gs-helper.h"
#include <math.h>

//Comment / uncomment the below line to hide / show arrays
#define DPRINT            //Whether to print debug messages / arrays

//Sequential Gauss-Seidel solver
void gauss_seidel_sequential(int asize) {
  float *A, maxError, oldValue;
  init_arrays(SEED,asize,&A);

  for(int it = 1; it <= MAXIT; ++it) {  //Repeat the estimation process 1000 times
    for (int i = 1; i < asize-1; ++i) {
      for (int j = 1; j < asize-1; ++j) {
        oldValue = A[IND(i,j,asize)];
        A[IND(i,j,asize)] = 0.25*(
          A[IND(i-1,j,asize)] +
          A[IND(i+1,j,asize)] +
          A[IND(i,j-1,asize)] +
          A[IND(i,j+1,asize)]
        );
      }
    }
  }

  #ifdef DPRINT
    for(int i = 0; i < asize; i+=asize/5)
      printf("  A[%4d,%4d]=%7.10f\n", i,i,A[IND(i,i,asize)]);
  #endif

  clean_arrays(&A);
}

//Parallel Gauss-Seidel solver using a spinlock (signal wait)
void gauss_seidel_pipelined(int num_threads, int asize, int tilesize) {
  float *A;
  init_arrays(SEED,asize,&A);

  //lastTileDone[i] tracks the last block completed by thread i
  int* lastTileDone = (int *)malloc(sizeof(int)*num_threads);

  for(int it = 1; it <= MAXIT; ++it) {
    for(int i = 0; i < num_threads; ++i)
      lastTileDone[i] = -1;
    #pragma omp parallel num_threads(num_threads)
    {
      int nthreads = omp_get_num_threads();
      int tid = omp_get_thread_num();

      int startrow = (tid*asize)/nthreads;
      int endrow = ((tid+1)*asize)/nthreads;

      for (int jBegin = 1; jBegin < asize-2; jBegin += tilesize) {

        //////////////////////////////////////////////////////
        //Add code here to wait for the tile being processed//
        //      by the previous processor if necessary      //
        //////////////////////////////////////////////////////

	for (int i = MAX(1,startrow); i < MIN(asize-1,endrow); ++i) {
		for (int j = jBegin; j < MIN(asize-1,jBegin + tilesize); ++j) {
            //omittiong convergence test	    oldValue = A[IND(i,j,asize)];
			if(omp_get_thread_num() > 0)
				while(lastTileDone[tid-1] < jBegin){
				#pragma omp flush
				}

			A[IND(i,j,asize)] = 0.25*(
			A[IND(i-1,j,asize)] +
			A[IND(i+1,j,asize)] +
			A[IND(i,j-1,asize)] +
			A[IND(i,j+1,asize)]);
		}
        }
        lastTileDone[tid] = jBegin;
      }
    }
  }

  #ifdef DPRINT
    for(int i = 0; i < asize; i+=asize/5)
      printf("  A[%4d,%4d]=%7.10f\n", i,i,A[IND(i,i,asize)]);
  #endif

  free(lastTileDone);
  clean_arrays(&A);
}

//Parallel Gauss-Seidel solver using diagonal striping
void gauss_seidel_diagonal(int num_threads, int asize) {
  float *A;
  init_arrays(SEED,asize,&A);

  for(int it = 1; it <= MAXIT; it += 1) {
    for(int diag = 2; diag < (asize+asize-3); diag += 1) {
      #pragma omp parallel for num_threads(num_threads)
      for(int i = MAX(1,diag-asize+2); i < MIN(diag,asize-1); ++i) {
        int j = diag-i;
        if (j > 0 && j < asize-1) {
  	      A[IND(i,j,asize)] = 0.25*(
            A[IND(i-1,j,asize)] +
            A[IND(i+1,j,asize)] +
  		      A[IND(i,j-1,asize)] +
            A[IND(i,j+1,asize)]
          );
        }
      }
    }
  }

  #ifdef DPRINT
    for(int i = 0; i < asize; i+=asize/5)
      printf("  A[%4d,%4d]=%7.10f\n", i,i,A[IND(i,i,asize)]);
  #endif

  clean_arrays(&A);
}

int main() {
  int ncores       = omp_get_max_threads();
  int threads[]    = {1,ncores/2,ncores};
  int asizes[]     = {32,128,512,2048};
  int tilesizes[]  = {2,4,8,16,32};

  printf("Testing Gauss-Seidel for %i iterations\n",MAXIT);
  for (int i = 0; i < sizeof(asizes) / sizeof(asizes[0]); ++i) {
    time_seqn(asizes[i]);
    for (int j = 0; j < sizeof(threads) / sizeof(threads[0]); ++j) {
      for (int k = 0; k < sizeof(tilesizes) / sizeof(tilesizes[0]); ++k) {
        time_pipe(threads[j],asizes[i],tilesizes[k]);
      }
      time_diag(threads[j],asizes[i]);
    }
  }

  return 0;
}
