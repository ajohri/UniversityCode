#ifndef __MATRIX_H_
#define __MATRIX_H_
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <algorithm>

void basic_implementation(double *, double *,int,int);
void basic_flipped(double *,double *,int,int);
void basic_unrolled_4(double *,double *,int,int);
void basic_unrolled_8(double *,double *,int,int);
void basic_block(double *,double *,int,int,int,int);

#endif
