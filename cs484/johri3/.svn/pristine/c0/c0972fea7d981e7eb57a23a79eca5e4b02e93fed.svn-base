#include "matrix.h"

void basic_flipped(double *A, double *B, int num_rows, int num_cols)
{
	assert (A != NULL);
	assert (B != NULL);

	/*The flipped version of your implementation should go here
	  i.e write accesses should be strided. The matrix that is
	being updated should be accessed in column-major order*/
	for(int j = 0; j < num_rows; j++) {
		for(int i = 0; i < num_cols; i++) {
			A[(i * num_cols) + j] = B[(j * num_rows) + i];
		}
	}



}
