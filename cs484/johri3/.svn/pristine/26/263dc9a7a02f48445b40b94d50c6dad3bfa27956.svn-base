#include "matrix.h"

void basic_implementation(double *A, double *B, int num_rows, int num_cols)
{
	assert (A != NULL);
	assert (B != NULL);


	/*The vanilla version of matrix transpose should go here*/
	/*Write accesses should be contiguous for the vanilla version,
	  i.e the matrix that is being updated should be accessed in
	  row-major order*/
		for(int i = 0; i < num_rows; i++) {
			for(int j = 0; j < num_cols; j++) {
				A[(i * num_cols) + j] = B[(j * num_rows) + i];
			}
		}



}
