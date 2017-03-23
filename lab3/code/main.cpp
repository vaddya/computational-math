#include <c++/fstream>
#include "main.h"

int main() {
    double **exact = evalExact(N, POINTS);
    double **rkf = evalRkf45(N, POINTS);
    double **euler = evalImpEuler(N, POINTS, STEP);
    double **error = new double *[POINTS];
    for (int i = 0; i < POINTS; i++) {
        error[i] = new double[N];
        for (int j = 0; j < N; j++) {
            error[i][j] = abs(exact[i][j] - euler[i][j]);
        }
    }

    printTable("exact", exact, N, POINTS);
    printTable("rkf45", rkf, N, POINTS);
    printTable("impeuler", euler, N, POINTS);
    printTable("|exact - impeuler|", error, N, POINTS);

    printCsv("exact", "t, x1, x2", exact, N, POINTS);
    printCsv("rkf45", "t, x1, x2", exact, N, POINTS);
    printCsv("euler", "t, x1, x2", euler, N, POINTS);
    printCsv("euler_error", "t, x1, x2", error, N, POINTS);
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
    double t;
    double **values = new double *[points];
    for (int i = 0; i < points; i++) {
        values[i] = new double[n];
    }
    for (int i = 0; i < n; ++i) {
        values[0][i] = x[i];
    }
    for (int i = 1; i < points; i++) {
        t = getStep(i - 1);
        impEuler(fun, n, x, t, step);
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
        cout << setprecision(1)
             << getStep(i) << ":\t(";
        for (int j = 0; j < n; ++j) {
            cout << setprecision(8)
                 << values[i][j]
                 << (j != n - 1 ? ", " : ")\n");
        }
    }
}

void printCsv(string table, string cols, double **values, int n, int points) {
    string filename = "../../data/" + table + ".csv";
    ofstream out(filename);

    out << cols << endl;
    for (int i = 0; i < points; i++) {
        out << setprecision(2)
             << getStep(i) << ", ";
        for (int j = 0; j < n; ++j) {
            out << setprecision(8)
                 << values[i][j]
                 << (j != n - 1 ? ", " : "\n");
        }
    }

    out.close();
}