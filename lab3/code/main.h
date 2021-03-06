#ifndef LAB2_MAIN_H_H
#define LAB2_MAIN_H_H

#include <c++/iostream>
#include <c++/cmath>
#include <c++/iomanip>
#include "rkf45.h"
#include "impeuler.h"

using namespace std;

const int N = 2;
const double START = 1.0;
const double END = 2.0;
const double STEP = 0.1;
const int POINTS = (const int) ((END - START) / STEP + 1);

int main();

double **evalExact(int n, int points);

double **evalRkf45(int n, int points);

double **evalImpEuler(int n, int points, double step);

void fun(double t, double *x, double *dx);

double getStep(int i);

void printTable(string table, double **values, int n, int points);

void printCsv(string table, string cols, double **values, int n, int points);

#endif