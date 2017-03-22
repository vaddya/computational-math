#include "main.h"

const int N = 2;
const double START = 1.0;
const double END = 2.0;
const double STEP = 0.1;
const int POINTS = (const int) ((END - START) / STEP + 1);

int main() {
    printTable("EXACT", evalExact(N, POINTS), N, POINTS);
    printTable("RKF45", evalRkf45(N, POINTS), N, POINTS);
    printTable("RKF45", evalImpEuler(N, POINTS, STEP), N, POINTS);
    return 0;
}

double **evalExact(int n, int points) {
    double **values = new double *[points];
    for (int i = 0; i < points; i++) {
        values[i] = new double[n];
    }
    for (int i = 0; i < points; ++i) {
        double t = getStep(i);
        values[i][0] = pow(t, 4);
        values[i][1] = 4 * pow(t, 3);
    }
    return values;
}

double **evalRkf45(int n, int points) {
    double x[] = {1, 4};
    double t = 1.0;
    double tout;
    double relerr = 1e-10;
    double abserr = 1e-10;
    int flag;
    double work[15];
    int iwork[5];
    double **values = new double *[points];
    for (int i = 0; i < points; i++) {
        values[i] = new double[n];
    }

    for (int i = 0; i < points; i++) {
        tout = getStep(i);
        flag = 1;
        RKF45(fun, n, x, &t, &tout, &relerr, &abserr, &flag, work, iwork);
        for (int j = 0; j < n; ++j) {
            values[i][j] = x[j];
        }
    }
    return values;
}

double **evalImpEuler(int n, int points, double step) {
    double x[] = {1, 4};
    double t = 1.0;
    double tout;
    double work[15];
    int iwork[5];
    double **values = new double *[points];
    for (int i = 0; i < points; i++) {
        values[i] = new double[n];
    }

    for (int i = 0; i < points; i++) {
        tout = getStep(i);
        impEulerMethod(fun, n, x, t, tout, step);
        for (int j = 0; j < n; ++j) {
            values[i][j] = x[j];
        }
    }
    return values;
}

void fun(double t, double *x, double *dx) {
    dx[0] = 0 * x[0] + 1 * x[1];
    dx[1] = (12 / (t * t)) * x[0];
}

double getStep(int i) {
    return START + STEP * i;
}

void printTable(string table, double **values, int n, int points) {
    cout << endl << table << endl;
    cout << fixed;
    for (int i = 0; i < points; i++) {
        cout << setprecision(2)
             << getStep(i) << ":\t(";
        for (int j = 0; j < n; ++j) {
            cout << setprecision(8)
                 << values[i][j]
                 << (j != n - 1 ? ", " : ")\n");
        }
    }
}