#ifndef LAB3_IMPROVEDEULER_H
#define LAB3_IMPROVEDEULER_H

typedef void (*Fun)(double t, double *x, double *dx);

void impEuler(Fun fun, int n, double *x, double t, double h);

#endif
