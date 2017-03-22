#ifndef LAB3_IMPROVEDEULER_H
#define LAB3_IMPROVEDEULER_H

typedef void (*Fun)(double TT, double *X, double *DX);

double **impEulerMethod(Fun fun, int n, double *x, double t, double tout, double step);

#endif //LAB3_IMPROVEDEULER_H
