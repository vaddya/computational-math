#include <c++/array>
#include <c++/iostream>
#include "matrix.h"

using namespace std;
using matrix::Matrix;
using T = double;
const int N = 8;
const int M = 8;

Matrix<T, N, M> findMatrixR(Matrix<T, N, M> matrix) {
    return matrix * matrix::invert(matrix) - matrix::identity<T, N>();
}

int main() {
    const T paramValues[] = {1, 0.1, 0.01, 0.001, 0.00001};
    for (double p : paramValues) {
        const T values[N][M] = {
                {p + 13, 2,  8,  -7, 7,  5,  -7, -7},
                {7,      2,  -4, 2,  3,  3,  -1, -2},
                {-7,     2,  1,  3,  6,  -6, -3, -4},
                {-2,     -8, -6, -1, 6,  2,  1,  -4},
                {0,      4,  -7, 1,  22, 0,  -6, -6},
                {0,      -3, -6, 6,  4,  13, 0,  6},
                {-8,     -6, -4, 7,  -5, -5, -2, 1},
                {5,      5,  -2, -2, -3, 0,  -7, 14}
        };

        Matrix<T, N, M> matrixA(values);
        Matrix<T, N, M> matrixR = findMatrixR(matrixA);

        cout << "p = " << p << endl
             << "Matrix A^(-1): " << endl << matrix::invert(matrixA)
             << "||R|| = A * A^(-1) - E = " << matrixR.norm() << endl << endl;
    }

    return 0;
}