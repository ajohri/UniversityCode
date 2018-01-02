#include "matrix.h"

/*You are free to increase/decrease the unroll factors if you want to do more experiments*/


void basic_unrolled_4(double *A, double *B, int num_rows, int num_cols)
{
	assert (A != NULL);
	assert (B != NULL);

	/*The unrolled version of your vanilla implementation should go here,
	use an unroll factor of 4 for this function*/
	for(int i = 0; i < num_rows; i += 4) {
		for(int j = 0; j < num_cols; j++) {
			A[(i * num_cols) + j] = B[(j * num_rows) + i];
			A[((i + 1) * num_cols) + j] = B[(j * num_rows) + (i + 1)];
			A[((i + 2) * num_cols) + j] = B[(j * num_rows) + (i + 2)];
			A[((i + 3) * num_cols) + j] = B[(j * num_rows) + (i + 3)];
		}
	}


}

void basic_unrolled_8(double *A, double *B, int num_rows, int num_cols)
{
	assert (A != NULL);
	assert (B != NULL);

	/*The unrolled version of your vanilla implementation should go here,
	use an unroll factor of 8 for this function*/

	for(int i = 0; i < num_rows; i += 8) {
		for(int j = 0; j < num_cols; j++) {
			A[(i * num_cols) + j] = B[(j * num_rows) + i];
			A[((i + 1) * num_cols) + j] = B[(j * num_rows) + (i + 1)];
			A[((i + 2) * num_cols) + j] = B[(j * num_rows) + (i + 2)];
			A[((i + 3) * num_cols) + j] = B[(j * num_rows) + (i + 3)];
			A[((i + 4) * num_cols) + j] = B[(j * num_rows) + (i + 4)];
			A[((i + 5) * num_cols) + j] = B[(j * num_rows) + (i + 5)];
			A[((i + 6) * num_cols) + j] = B[(j * num_rows) + (i + 6)];
			A[((i + 7) * num_cols) + j] = B[(j * num_rows) + (i + 7)];
		}
	}



}
