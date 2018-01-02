#include "matrix.h"

void basic_block(double *A, double *B, int num_rows, int num_cols, int block_size_x, int block_size_y)
{

	assert (A != NULL);
	assert (B != NULL);



	/*The 2D-tiled version of matrix transpose should go here
	  tile sizes are accepted as inputs*/
		for(int i = 0; i < num_rows; i += block_size_x) {
			for(int j = 0; j < num_cols; j += block_size_y) {
				for(int ii = i; ii < i + block_size_x; ii++) {
					for(int jj = j; jj < j + block_size_y; jj++) {
						A[(ii * num_cols) + jj] = B[(jj * num_rows) + ii];
					}
				}
			}
		}


}

/*You are free to add unrolling to the tiled version if you want to do more experiments*/
