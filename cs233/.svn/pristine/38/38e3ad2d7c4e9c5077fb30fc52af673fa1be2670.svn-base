#include <xmmintrin.h>
#include "mandelbrot.h"

// cubic_mandelbrot() takes an array of SIZE (x,y) coordinates --- these are
// actually complex numbers x + yi, but we can view them as points on a plane.
// It then executes 200 iterations of f, using the <x,y> point, and checks
// the magnitude of the result; if the magnitude is over 2.0, it assumes
// that the function will diverge to infinity.

// vectorize the code below using SIMD intrinsics
int *
cubic_mandelbrot_vector(float x[SIZE], float y[SIZE]) {
  static int ret[SIZE];
 __m128 x1, y1, x2, y2, X1SQUARED, Y1SQUARED, otherX1SQUARED, otherY1SQUARED, comparison, xati, yati, subval, addsquares, xmuly;

 comparison = _mm_set1_ps(M_MAG *M_MAG);

 for (int i = 0 ; i < SIZE ; i +=4) {
    x1 = _mm_set1_ps(0.0);
    y1 = _mm_set1_ps(0.0);
    xati = _mm_loadu_ps(&x[i]);
    yati = _mm_loadu_ps(&y[i]);
    // Run M_ITER iterations
    for (int j = 0 ; j < M_ITER ; j ++) {
       // Calculate the real part of (x1 + y1 * i)^2 + (x + y * i)
       X1SQUARED = _mm_mul_ps(x1, x1);
       Y1SQUARED = _mm_mul_ps(y1, y1);
       subval = _mm_sub_ps(X1SQUARED, Y1SQUARED);
       x2 = _mm_add_ps(xati, subval);

       //x2 = (x1 * x1) - (y1 * y1) + x[i];

       // Calculate the imaginary part of (x1 + y1 * i)^2 + (x + y * i)

       xmuly = _mm_mul_ps(x1, y1);
       y2 = _mm_add_ps(yati, _mm_add_ps(xmuly, xmuly));

       //y2 = 2 * (x1 * y1) + y[i];

       // Use the new complex number as input for the next iteration
       x1 = x2;
       y1 = y2;
    }

    otherX1SQUARED = _mm_mul_ps(x2, x2);
    otherY1SQUARED = _mm_mul_ps(y2, y2);
    addsquares = _mm_add_ps(otherX1SQUARED, otherY1SQUARED);
    _mm_storeu_ps((float *)&ret[i], _mm_cmplt_ps(addsquares, comparison));
    // caculate the magnitude of the result
    // We could take the square root, but instead we just
    // compare squares
    //ret[i] = ((x2 * x2) + (y2 * y2)) < (M_MAG * M_MAG);
 }

 return ret;
}
