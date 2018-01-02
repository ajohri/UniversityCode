//Helper functions for Gauss-Seidel solver

#include "gs-helper.h"

//Get the current time
double get_time() {
  struct timeval tv;
  gettimeofday(&tv,0);
  return (tv.tv_sec*1.0+tv.tv_usec*1e-6);
}

//Record the execution time of one of the Gauss-Seidel functions
void time_seqn(int asize) {
  double start = get_time();
  gauss_seidel_sequential(asize);
  double end = get_time();
  printf("----Sequential, %ix%i matrix",asize,asize);
  printf("\tTook %lf seconds\n\n",end-start);
}

//Record the execution time of one of the Gauss-Seidel functions
void time_diag(int threads, int asize) {
  double start = get_time();
  gauss_seidel_diagonal(threads,asize);
  double end = get_time();
  printf("----Diagonal, %i threads, %ix%i matrix",threads,asize,asize);
  printf("\tTook %lf seconds\n\n",end-start);
}

//Record the execution time of one of the Gauss-Seidel functions
void time_pipe(int threads, int asize, int tilesize) {
  double start = get_time();
  gauss_seidel_pipelined(threads,asize,tilesize);
  double end = get_time();
  printf("----Pipelined, %i threads, %ix%i matrix, tilesize %i",threads,asize,asize,tilesize);
  printf("\tTook %lf seconds\n\n",end-start);
}

//Allocate memory for and initiallize arrays
void init_arrays(int seed, int asize, float **A) {
  //Allocate memory
  *A = (float *)malloc(sizeof(float*)*asize*asize);

  //Initialize the contents of A (just putting something a small non-0 vlaue
  for(int i = 0; i < asize; ++i) {
    for(int j = 0; j < asize; ++j) {
      (*A)[IND(i,j,asize)] = 0.001;
    }
  }

  for(int i = 0; i < asize; ++i) {
    (*A)[IND(i,0,asize)] = 0.5f*(float)i/(float)asize;
    (*A)[IND(i,asize-1,asize)] = 0.5f+0.5f*(float)i/(float)asize;
  }

  for(int j = 0; j < asize; ++j) {
    (*A)[IND(0,j,asize)] = 0.5f*(float)j/(float)asize;
    (*A)[IND(asize-1,j,asize)] = 0.5f+0.5f*(float)j/(float)asize;
  }
}

//Deallocate memory for arrays
void clean_arrays(float **A) {
  free(*A);
}
