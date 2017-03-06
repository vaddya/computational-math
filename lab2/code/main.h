#ifndef LAB2_MAIN_H_H
#define LAB2_MAIN_H_H

#include <c++/array>
#include <c++/iostream>
#include "matrix.h"

using namespace std;
using matrix::Matrix;
using T = double;
const int N = 8;
const int M = 8;

int main();

void doTask();

void doResearch(int pRange);

Matrix<T, N, M> findMatrixR(Matrix<T, N, M> matrix);

#endif
