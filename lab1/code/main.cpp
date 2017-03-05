#include <iostream>
#include <cmath>
#include "lagrange.h"
#include "quanc8.h"
#include "SPLINES.h"

using namespace std;

const int POINTS_NUM = 11;

double x[POINTS_NUM] = {};
double x_inter[POINTS_NUM] = {};
double f[POINTS_NUM] = {};

double function(double x0) {
    return 1 - exp(-x0);
}

double lagrange(double x0) {
    return lagrange(POINTS_NUM - 1, x, f, x0);
}

double spline(double x0) {
    double b[POINTS_NUM] = {};
    double c[POINTS_NUM] = {};
    double d[POINTS_NUM] = {};
    double x_spline[POINTS_NUM + 1] = {};
    double f_spline[POINTS_NUM + 1] = {};
    for (int i = 0; i < POINTS_NUM; i++) {
        x_spline[i + 1] = x[i];
        f_spline[i + 1] = f[i];
    }
    spline(POINTS_NUM, x_spline, f_spline, b, c, d);
    return seval(POINTS_NUM, &x0, x_spline, f_spline, b, c, d);
}

int main() {
    for (int i = 0; i < POINTS_NUM; i++) {
        x[i] = 0.3 * i;
        x_inter[i] = x[i] + 0.15;
        f[i] = function(x[i]);
    }

    /*
    printf("%4s %16s %16s %16s\n", "x", "f(x)", "l(x)", "s(x)");
    for (int i = 0; i < POINTS_NUM; i++) {
        printf("%4.2f %16.12f %16.12f %16.12f\n", x[i], function(x[i]), lagrange(x[i]), spline(x[i]));
        printf("%4.2f %16.12f %16.12f %16.12f\n", x_inter[i], function(x_inter[i]), lagrange(x_inter[i]),
               spline(x_inter[i]));
    }
    */

    cout << "abserr, f-l, errest, nofun, flag" << endl;
    cout << "abserr, f-s, errest, nofun, flag" << endl;

    for (int i = 0; i < 35; i++) {
        double a = 0.0;
        double b = 3.0;
        double abserr = pow(10, (double) -i);
        double relerr = 0;
        double errest;
        int nofun;
        double flag;

        double int_fun;
        quanc8(function, a, b, abserr, relerr, &int_fun, &errest, &nofun, &flag);
        double int_lagrange;
        quanc8(lagrange, a, b, abserr, relerr, &int_lagrange, &errest, &nofun, &flag);
        double int_spline;
        quanc8(spline, a, b, abserr, relerr, &int_spline, &errest, &nofun, &flag);

        cout << abserr << ", "
             << fabs(int_fun - int_lagrange) << ", "
             << fabs(int_fun - int_spline) << ", "
             << errest << ", "
             << nofun << ", "
             << flag << endl;

        /*
        printf("\n%16s %18s %18s\n", "quanc8{f(x)}", "quanc8{l(x)}", "quanc8{s(x)}");
        printf("%16.14f %18.14f %18.14f\n", int_fun, int_lagrange, int_spline);

        printf("\n|quanc8{f(x)} - quanc8{l(x)}| = %.14f\n", fabs(int_fun - int_lagrange));
        printf("|quanc8{f(x)} - quanc8{s(x)}| = %.14f\n\n", fabs(int_fun - int_spline));
        */
    }
    return 0;
}
