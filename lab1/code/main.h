#ifndef LAB1_MAIN_H
#define LAB1_MAIN_H

#include <iomanip>
#include <iostream>
#include <cmath>
#include "lagrange.h"
#include "quanc8.h"
#include "splines.h"

using namespace std;

const int POINTS_NUM = 11;
const double POINTS_STEP = 0.3;

enum Mode {
    FUNCTION, LAGRANGE, SPLINE
};

double x[POINTS_NUM] = {};
double x_inter[POINTS_NUM] = {};
double f[POINTS_NUM] = {};

int main();

void doTask(int precision);

void doResearch(Mode mode);

double function(double x0);

double lagrange(double x0);

double spline(double x0);

#endif
