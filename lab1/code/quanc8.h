// quanc8.h

#ifndef _QUANC8
#define _QUANC8

void quanc8(double (*FUN)(double), double A, double B, double ABSERR,
			double RELERR, double *RESULT, double *ERREST, int *NOFUN, double *FLAG);

#endif