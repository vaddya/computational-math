#include "impeuler.h"

void impEuler(Fun fun, int n, double *x, double t, double h) {
    double dx[n];
    fun(t, x, dx);

    double x_sup[n];
    for (int i = 0; i < n; ++i) {
        x_sup[i] = x[i] + h * dx[i] / 2;
    }

    double t_sup = t + h / 2;
    double dx_sup[n];
    fun(t_sup, x_sup, dx_sup);

    for (int i = 0; i < n; ++i) {
        x[i] = x[i] + h * dx_sup[i];
    }
}