#include "main.h"

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
        x[i] = POINTS_STEP * i;
        x_inter[i] = x[i] + POINTS_STEP / 2;
        f[i] = function(x[i]);
    }
    doTask(14); // precision
    doResearch(LAGRANGE); // FUNCTION or LAGRANGE or SPLINE
    return 0;
}

void doTask(int precision) {
    cout << fixed
         << setw(4) << "x"
         << setw(precision + 5) << "f(x)"
         << setw(precision + 5) << "L(x)"
         << setw(precision + 5) << "S(x)" << endl;

    for (int i = 0; i < POINTS_NUM; i++) {
        cout << setprecision(2) << setw(4) << x_inter[i]
             << setprecision(precision) << setw(precision + 5) << function(x_inter[i])
             << setw(precision + 5) << lagrange(x_inter[i])
             << setw(precision + 5) << spline(x_inter[i]) << endl;
    }

    double a = 0.0;
    double b = 3.0;
    double abserr = 1e-14;
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

    cout << endl
         << setw(precision + 4) << "quanc8{f(x)}"
         << setw(precision + 4) << "quanc8{L(x)}"
         << setw(precision + 4) << "quanc8{S(x)}" << endl
         << setw(precision + 4) << int_fun
         << setw(precision + 4) << int_lagrange
         << setw(precision + 4) << int_spline << endl;

    cout << endl
         << "|quanc8{f(x)} - quanc8{L(x)}| = " << fabs(int_fun - int_lagrange) << endl
         << "|quanc8{f(x)} - quanc8{S(x)}| = " << fabs(int_fun - int_spline) << endl << endl;
}

void doResearch(Mode mode) {
    if (mode == FUNCTION) cout << "f(x)\nabserr, esterr, nofun, flag" << endl;
    if (mode == LAGRANGE) cout << "L(x)\nabserr, f-l, errest, nofun, flag" << endl;
    if (mode == SPLINE) cout << "S(x)\nabserr, f-s, errest, nofun, flag" << endl;

    for (int i = 0; i < 35; i++) {
        double a = 0.0;
        double b = 3.0;
        double abserr = pow(10, (double) -i);
        double relerr = 0;
        double errest;
        int nofun;
        double flag;

        double int_fun = 0;
        quanc8(function, a, b, abserr, relerr, &int_fun, &errest, &nofun, &flag);
        double int_lagrange = 0;
        if (mode == LAGRANGE) quanc8(lagrange, a, b, abserr, relerr, &int_lagrange, &errest, &nofun, &flag);
        double int_spline = 0;
        if (mode == SPLINE) quanc8(spline, a, b, abserr, relerr, &int_spline, &errest, &nofun, &flag);

        cout << defaultfloat << setprecision(6)
             << abserr << ", ";
        if (mode == LAGRANGE)cout << fabs(int_fun - int_lagrange) << ", ";
        if (mode == SPLINE) cout << fabs(int_fun - int_spline) << ", ";
        cout << errest << ", "
             << nofun << ", "
             << flag << endl;
    }
}
