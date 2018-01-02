#include <xmmintrin.h>
#include "mv-mult.h"

// Matrix-Vector multiplication
// mat is a SIZE by SIZE matrix, that is arranged in row-column, format,
// That is, you first select a particular row, and then a particular column.
// Each row is laid out as a one-dimensional, array, so if you wanted
// to select a particular row, you would use mat[row].  You can
// also select smaller intervals, by using &mat[row][col].
// The vector is also laid out as a one-dimensional arrow, similar to a row.
// M-V multiplication proceeds by taking the dot product of a matrix row
// with the vector, and doing this for each row in the matrix

// vectorize the below code using SIMD intrinsics
float *
mv_mult_vector(float mat[SIZE][SIZE], float vec[SIZE]) {
	static float ret[SIZE];
	__m128 acc, _mat, _vec;
	acc = _mm_set1_ps(0.0);

	for (int i = 0 ; i < SIZE ; i++) {
		float temp[4];
		ret[i] = 0;
		int j = 0;
		acc = _mm_set1_ps(0.0);
		for (j = 0 ; j < (SIZE-3) ; j+=4) {
			_mat = _mm_loadu_ps(&mat[i][j]);
			_vec = _mm_loadu_ps(&vec[j]);
			acc = _mm_add_ps(acc, _mm_mul_ps(_mat, _vec));
		}
		_mm_storeu_ps(temp, acc);
		ret[i] = temp[0] + temp[1] + temp[2] + temp[3];
		for(; j < SIZE; j++)
			ret[i] += mat[i][j] * vec[j];
	}

	return ret;
}
