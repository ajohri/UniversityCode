//Helper functions for Gauss-Seidel solver

#ifndef GS_HELPER_H
#define GS_HELPER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include "sys/time.h"

#define MAXIT  1000       //Maxinum number of iterations to allow
#define SEED   1486706860 //Random seed for matrix generation
#define MAGIC  2.324645f  //Arbitrary number designating unassigned value

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define IND(i,j,size) ((i)*(size)+(j))

void gauss_seidel_pipelined(int num_threads, int asize, int tilesize);
void gauss_seidel_diagonal(int num_threads, int asize);
void gauss_seidel_sequential(int asize);

//Get the current time
double get_time();

//Record the execution time of one of the Gauss-Seidel functions
void time_seqn(int asize);

//Record the execution time of one of the Gauss-Seidel functions
void time_diag(int threads, int asize);

//Record the execution time of one of the Gauss-Seidel functions
void time_pipe(int threads, int asize, int tilesize);

//Allocate memory for and initiallize arrays
void init_arrays(int seed, int asize, float **A);

//Deallocate memory for arrays
void clean_arrays(float **A);

#endif //#GS_HELPER_H
