#ifndef LAB3_RKF45_H
#define LAB3_RKF45_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Fun)(double TT, double *X, double *DX);

void RKF45(Fun FUN,
           int NEQN, double *Y, double *T, double *TOUT,
           double *RELERR, double *ABSERR,
           int *IFLAG, double *WORK, int *IWORK);

#ifdef __cplusplus
}
#endif

#endif //RKF45_H