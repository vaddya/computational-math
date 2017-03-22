#include <math.h>
#include <stdlib.h>
#include "rkf45.h"

double AMAX1(double a, double b) {
    if (a >= b) return a; else return b;
}

double AMIN1(double a, double b) {
    if (a <= b) return a; else return b;
}

double SIGN(double a, double b) {
    if (b == 0) return 0; else return (b / fabs(b) * fabs(a));
}

int ISIGN(int a, int b) {
    if (b == 0) return 0; else return (b / abs(b) * abs(a));
}

void FEHL(Fun fun, int NEQN,
          double *Y, double *T, double *H, double *YP,
          double *F1, double *F2, double *F3, double *F4, double *F5, double *S) {
    double CH;
    int K;
    CH = (*H) / 4.0;
    for (K = 1; K <= NEQN; K++)
        F5[K - 1] = Y[K - 1] + CH * YP[K - 1];
    fun(*T + CH, F5, F1);
    CH = 3.0 * (*H) / 32.0;
    for (K = 1; K <= NEQN; K++)
        F5[K - 1] = Y[K - 1] + CH * (YP[K - 1] + 3.0 * F1[K - 1]);
    fun(*T + 3.0 * (*H) / 8.0, F5, F2);
    CH = (*H) / 2197.0;
    for (K = 1; K <= NEQN; K++)
        F5[K - 1] = Y[K - 1] + CH * (1932.0 * YP[K - 1] + (7296.0 * F2[K - 1] - 7200.0 * F1[K - 1]));
    fun(*T + 12.0 * (*H) / 13.0, F5, F3);
    CH = (*H) / 4104.0;
    for (K = 1; K <= NEQN; K++)
        F5[K - 1] = Y[K - 1] + CH * ((8341.0 * YP[K - 1] - 845.0 * F3[K - 1]) +
                                     (29440.0 * F2[K - 1] - 32832.0 * F1[K - 1]));
    fun(*T + (*H), F5, F4);
    CH = (*H) / 20520.0;
    for (K = 1; K <= NEQN; K++)
        F1[K - 1] = Y[K - 1] + CH * ((-6080.0 * YP[K - 1] + (9295.0 * F3[K - 1] -
                                                             5643.0 * F4[K - 1])) +
                                     (41040.0 * F1[K - 1] - 28352.0 * F2[K - 1]));
    fun(*T + (*H) / 2.0, F1, F5);
    CH = (*H) / 7618050.0;
    for (K = 1; K <= NEQN; K++)
        S[K - 1] = Y[K - 1] + CH * ((902880.0 * YP[K - 1] + (3855735.0 * F3[K - 1] -
                                                             1371249.0 * F4[K - 1])) +
                                    (3953664.0 * F2[K - 1] + 277020.0 * F5[K - 1]));
}

void RKFS(Fun fun, int NEQN,
          double *Y, double *T, double *TOUT,
          double *RELERR, double *ABSERR, int *IFLAG,
          double *YP, double *H, double *F1, double *F2,
          double *F3, double *F4, double *F5, double *SAVRE,
          double *SAVAE, int *NFE, int *KOP, int *INIT, int *JFLAG,
          int *KFLAG) {
    int HFAILD, OUTPUT;
    double A, AE, DT, EE, EEOET, ESTTOL, ET, HMIN, REMIN,
            RER, S, SCALE, TOL, TOLN, U26, EPSP1, EPS, YPK;

    int K, MAXNFE, MFLAG;

    REMIN = 1.E-12;

    MAXNFE = 3000;
    if (NEQN < 1)goto l10;
    if ((*RELERR < 0.0) || (*ABSERR < 0.0)) goto l10;
    MFLAG = abs(*IFLAG);
    if ((MFLAG == 0) || (MFLAG > 8))goto l10;
    if (MFLAG != 1)goto l20;

    EPS = 1.0;
    l5:
    EPS = EPS / 2.0;
    EPSP1 = EPS + 1.;
    if (EPSP1 > 1.)goto l5;
    U26 = 26. * EPS;
    goto l50;
    l10:
    *IFLAG = 8;
    return;
    l20:
    if ((*T == *TOUT) && (*KFLAG != 3))goto l10;
    if (MFLAG != 2)goto l25;
    if ((*KFLAG == 3) || (*INIT == 0))goto l45;
    if (*KFLAG == 4)goto l40;
    if ((*KFLAG == 5) && (*ABSERR == 0.0))goto l30;
    if ((*KFLAG == 6) && (*RELERR <= *SAVRE) &&
        (*ABSERR <= *SAVAE))
        goto l30;
    goto l50;

    l25:
    if (*IFLAG == 3)goto l45;
    if (*IFLAG == 4)goto l40;
    if ((*IFLAG == 5) && (*ABSERR > 0.0))goto l45;

    l30:
    goto l35;
    l35:
    exit(0);

    l40:
    *NFE = 0;
    if (MFLAG == 2)goto l50;

    l45:
    *IFLAG = *JFLAG;
    if (*KFLAG == 3)MFLAG = abs(*IFLAG);

    l50:
    *JFLAG = *IFLAG;
    *KFLAG = 0;

    *SAVRE = *RELERR;
    *SAVAE = *ABSERR;
    RER = 2. * EPS + REMIN;
    if (*RELERR >= RER)goto l55;
    *RELERR = RER;
    *IFLAG = 3;
    *KFLAG = 3;
    return;
    l55:
    DT = *TOUT - *T;
    if (MFLAG == 1)goto l60;
    if (*INIT == 0)goto l65;
    goto l80;

    l60:
    *INIT = 0;
    *KOP = 0;
    A = *T;
    fun(A, Y, YP);
    *NFE = 1;
    if (*T != *TOUT)goto l65;
    *IFLAG = 2;
    return;
    l65:
    *INIT = 1;
    *H = fabs(DT);
    TOLN = 0.;
    for (K = 1; K <= NEQN; K++) {
        TOL = (*RELERR) * fabs(Y[K - 1]) + (*ABSERR);
        if (TOL <= 0)goto l70;
        TOLN = TOL;
        YPK = fabs(YP[K - 1]);
        if (YPK * pow((*H), 5) > TOL) *H = pow((TOL / YPK), 0.2);
    }
    l70:
    if (TOLN <= 0.0) *H = 0.0;
    *H = AMAX1(*H, U26 * AMAX1(fabs(*T), fabs(DT)));
    *JFLAG = ISIGN(2, *IFLAG);
    l80:
    *H = SIGN(*H, DT);
    if (fabs(*H) >= 2.0 * fabs(DT))*KOP = *KOP + 1;
    if (*KOP != 100)goto l85;
    *KOP = 0;
    *IFLAG = 7;
    return;
    l85:
    if (fabs(DT) > U26 * fabs(*T))goto l95;
    for (K = 1; K <= NEQN; K++) {
        Y[K - 1] = Y[K - 1] + DT * YP[K - 1];
    }
    l90:
    A = *TOUT;
    fun(A, Y, YP);
    *NFE = *NFE + 1;
    goto l300;
    l95:
    OUTPUT = 0;
    SCALE = 2. / (*RELERR);
    AE = SCALE * (*ABSERR);
    l100:
    HFAILD = 0;
    HMIN = U26 * fabs(*T);
    DT = *TOUT - (*T);
    if (fabs(DT) >= 2. * fabs(*H))goto l200;
    if (fabs(DT) > fabs(*H))goto l150;
    OUTPUT = 1;
    *H = DT;
    goto l200;
    l150:
    *H = 0.5 * DT;
    l200:
    if (*NFE <= MAXNFE)goto l220;
    *IFLAG = 4;
    *KFLAG = 4;
    return;
    l220:
    FEHL(fun, NEQN, Y, T, H, YP, F1, F2, F3, F4, F5, F1);
    *NFE = *NFE + 5;
    EEOET = 0.;
    for (K = 1; K <= NEQN; K++) {
        ET = fabs(Y[K - 1]) + fabs(F1[K - 1]) + AE;
        if (ET > 0.)goto l240;
        *IFLAG = 5;
        *KFLAG = 5;
        return;
        l240:
        EE = fabs((-2090. * YP[K - 1] + (21970. * F3[K - 1] - 15048. * F4[K - 1]))
                  + (22528. * F2[K - 1] - 27360. * F5[K - 1]));
        EEOET = AMAX1(EEOET, EE / ET);
    }
    l250:
    ESTTOL = fabs(*H) * EEOET * SCALE / 752400.;
    if (ESTTOL <= 1.0)goto l260;
    HFAILD = 1;
    OUTPUT = 0;
    S = 0.1;
    if (ESTTOL < 59049.)S = 0.9 / pow(ESTTOL, 0.2);
    *H = S * (*H);
    if (fabs(*H) > HMIN)goto l200;
    *IFLAG = 6;
    *KFLAG = 6;
    return;
    l260:
    *T = *T + (*H);
    for (K = 1; K <= NEQN; K++)
        Y[K - 1] = F1[K - 1];
    l270:
    A = *T;
    fun(A, Y, YP);
    *NFE = *NFE + 1;
    S = 5.;
    if (ESTTOL > 1.889568E-4)S = 0.9 / pow(ESTTOL, 0.2);
    if (HFAILD)S = AMIN1(S, 1.0);
    *H = SIGN(AMAX1(S * fabs(*H), HMIN), *H);
    if (OUTPUT)goto l300;
    if (*IFLAG > 0)goto l100;
    *IFLAG = -2;
    return;
    l300:
    *T = *TOUT;
    *IFLAG = 2;
    return;
}

void RKF45(Fun FUN,
           int NEQN, double *Y, double *T, double *TOUT,
           double *RELERR, double *ABSERR,
           int *IFLAG, double *WORK, int *IWORK) {
    int K1, K2, K3, K4, K5, K6, K1M;
    K1M = NEQN + 1;
    K1 = K1M + 1;
    K2 = K1 + NEQN;
    K3 = K2 + NEQN;
    K4 = K3 + NEQN;
    K5 = K4 + NEQN;
    K6 = K5 + NEQN;

    RKFS(FUN, NEQN, Y, T, TOUT, RELERR, ABSERR, IFLAG,
         &WORK[0], &WORK[K1M - 1], &WORK[K1 - 1], &WORK[K2 - 1],
         &WORK[K3 - 1], &WORK[K4 - 1], &WORK[K5 - 1], &WORK[K6 - 1],
         &WORK[K6], &IWORK[0], &IWORK[1],
         &IWORK[2], &IWORK[3], &IWORK[4]);
}