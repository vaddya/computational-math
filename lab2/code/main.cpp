#include <c++/array>
#include <c++/iostream>
#include "matrix.h"

using namespace std;

int main() {
    const int size = 8;
    double p = 1.0;
    double values[size][size] = {
            {p + 13, 2,  8,  -7, 7,  5,  -7 - 7},
            {7,      2,  -4, 2,  3,  3,  -1, -2},
            {-7,     2,  1,  3,  6,  -6 - 3 - 4},
            {-2,     -8, -6, -1, 6,  2,  1,  -4},
            {0,      4,  -7, 1,  22, 0,  -6, -6},
            {0,      -3, -6, 6,  4,  13, 0,  6},
            {-8,     -6, -4, 7,  -5, -5, -2, 1},
            {5,      5,  -2, -2, -3, 0,  -7, 14}
    };

    double *pointer[size];
    for (int i = 0; i < size; ++i) {
        pointer[i] = values[i];
    }

    Matrix<double> matrix(size, size, pointer);
    matrix[1][0] = 5;
    cout << matrix << endl;
    cout << matrix.norm() << endl;
    return 0;
}