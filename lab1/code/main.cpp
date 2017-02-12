#include <iostream>
#include <cmath>
#include "lagrange.h"
#include "quanc8.h"
#include "SPLINES.h"

using namespace std;

const int POINTS_NUM = 11; // количество узлов интерполяции

double x[POINTS_NUM] = {}; // узлы интерполяции
double x_inter[POINTS_NUM] = {}; // промежуточные узлы
double f[POINTS_NUM] = {}; // значения функции в узлах

// Вычисление значения исходной фукнции в точке x0
double function(double x0) {
    return 1 - exp(-x0);
}

// Вычисление значения полинома Лагрнаджа в точке x0
double lagrange(double x0) {
    return lagrange(POINTS_NUM - 1, x, f, x0);
}

// Вычисление значения сплайн фукнции в точке x0
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

    printf("%4s %16s %16s %16s\n", "x", "f(x)", "l(x)", "s(x)");
    for (int i = 0; i < POINTS_NUM; i++) {
        printf("%4.2f %16.12f %16.12f %16.12f\n", x[i], function(x[i]), lagrange(x[i]), spline(x[i]));
        printf("%4.2f %16.12f %16.12f %16.12f\n", x_inter[i], function(x_inter[i]), lagrange(x_inter[i]),
               spline(x_inter[i]));
    }

    double a = 0.0; // нижний предел интегрирования
    double b = 3.0; // верхний предел интегрирования
    double abserr = 1.0E-14; // абсолютная погрешность
    double relerr = 0; // относительная погрешности
    double errest; // реальная погрешность
    int nofun; // количество внутренних вычислений функции
    double flag; // индикатор надёжности

    double int_fun; // Значение интеграла от заданной функции
    quanc8(function, a, b, abserr, relerr, &int_fun, &errest, &nofun, &flag);
    double int_lagrange; // Значение интеграла от полинома Лагранджа
    quanc8(lagrange, a, b, abserr, relerr, &int_lagrange, &errest, &nofun, &flag);
    double int_spline; // Значение интеграла от сплайн функции
    quanc8(spline, a, b, abserr, relerr, &int_spline, &errest, &nofun, &flag);

    printf("\n%16s %18s %18s\n", "quanc8{f(x)}", "quanc8{l(x)}", "quanc8{s(x)}");
    printf("%16.14f %18.14f %18.14f\n", int_fun, int_lagrange, int_spline);

    printf("\n|quanc8{f(x)} - quanc8{l(x)}| = %.14f\n", fabs(int_fun - int_lagrange));
    printf("|quanc8{f(x)} - quanc8{s(x)}| = %.14f\n\n", fabs(int_fun - int_spline));

    return 0;
}
