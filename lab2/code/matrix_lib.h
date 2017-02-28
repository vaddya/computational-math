#ifndef LAB2_MATRIX_LIB_H
#define LAB2_MATRIX_LIB_H

#include <math.h>

void solve(int n, double **a, double *b, int *ipvt);

void decomp(int n, double **a, double *cond, int *ipvt, double *work);

#endif //LAB2_MATRIX_LIB_H
