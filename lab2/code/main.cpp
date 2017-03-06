#include "main.h"

int main() {
    doTask();
    doResearch(15);
    return 0;
}

void doTask() {
    const T paramValues[] = {1, 0.1, 0.01, 0.001, 0.00001};
    for (auto p : paramValues) {
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
             << "||R|| = ||A * A^(-1) - E|| = " << matrixR.norm() << endl << endl;
    }
}

void doResearch(int pRange) {
    cout << "Research" << endl
         << "p, r_norm" << endl;
    for (int i = 0; i < pRange; ++i) {
        T p = pow(10, -i);
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

        cout << p << ", " << matrixR.norm() << endl;
    }
}

Matrix<T, N, M> findMatrixR(Matrix<T, N, M> matrix) {
    Matrix<T, N, M> inverted = matrix::invert(matrix);
    Matrix<T, N, M> identity = matrix::identity<T, N>();
    return matrix * inverted - identity;
}