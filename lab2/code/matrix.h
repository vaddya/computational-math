#ifndef MATRIX_H
#define MATRIX_H

#include <c++/cstdlib>
#include <c++/ostream>
#include <c++/iomanip>
#include "matrix_lib.h"

using namespace std;

namespace matrix {

    template<typename T, size_t N, size_t M>
    class Matrix {
    public:
        Matrix() {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    values[i][j] = 0;
                }
            }
        }

        Matrix(const T values[N][M]) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    this->values[i][j] = values[i][j];
                }
            }
        }

        Matrix(const Matrix<T, N, M> &rhs) : Matrix(rhs.values) {}

        Matrix<T, N, M> &operator=(const Matrix<T, N, M> &rhs) {
            if (this != &rhs) {
                memcpy(values, rhs.values, sizeof(values));
            }
            return *this;
        }

        T const *operator[](int i) const {
            return &values[i][0];
        }

        T *operator[](int i) {
            return &values[i][0];
        }

        int rows() const {
            return N;
        }

        int cols() const {
            return M;
        }

        T norm() const {
            T max = 0;
            for (int i = 0; i < rows(); i++) {
                T sum = 0;
                for (int j = 0; j < cols(); j++) {
                    sum += abs(values[i][j]);
                }
                max = sum > max ? sum : max;
            }
            return max;
        }

        Matrix<T, N, M> &operator+=(const Matrix<T, N, M> &rhs) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    values[i][j] += rhs.values[i][j];
                }
            }
            return *this;
        }

        Matrix<T, N, M> &operator-=(const Matrix<T, N, M> &rhs) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    values[i][j] -= rhs.values[i][j];
                }
            }
            return *this;
        }

        friend Matrix<T, N, M> operator+(Matrix<T, N, M> lhs, const Matrix<T, N, M> &rhs) {
            lhs += rhs;
            return lhs;
        }

        friend Matrix<T, N, M> operator-(Matrix<T, N, M> lhs, const Matrix<T, N, M> &rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend ostream &operator<<(ostream &os, const Matrix<T, N, M> &matrix) {
            os << setprecision(2);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    os << setw(11) << matrix[i][j];
                }
                os << '\n';
            }
            return os;
        }

        virtual ~Matrix() {}

    private:
        T values[N][M];

        T abs(T value) const {
            return value >= 0 ? value : -value;
        }
    };

    template<typename T, size_t N1, size_t M1, size_t N2, size_t M2>
    Matrix<T, N1, M2> operator*(Matrix<T, M1, N1> lhs, const Matrix<T, M2, N2> &rhs) {
        if (M2 != N1) {
            return Matrix<T, N1, M2>();
        }
        Matrix<T, N1, M2> res;
        for (int i = 0; i < N1; i++) {
            for (int j = 0; j < M2; j++) {
                for (int k = 0; k < M1; k++) {
                    res[i][j] += lhs[i][k] * rhs[k][j];
                }
            }
        }
        return res;
    }

    template<size_t N>
    Matrix<double, N, N> invert(const Matrix<double, N, N> &matrix) {
        double inverted[N][N];
        double work[N];
        double cond;
        int ipvt[N];
        double **lu = new double *[N];
        for (int i = 0; i < N; ++i) {
            lu[i] = new double[N];
            for (int j = 0; j < N; ++j) {
                lu[i][j] = matrix[i][j];
            }
        }
        decomp(N, lu, &cond, ipvt, work);
        for (int i = 0; i < N; i++) {
            double vector[N];
            for (int j = 0; j < N; j++) {
                vector[j] = 0;
            }
            vector[i] = 1.0;
            solve(N, lu, vector, ipvt);
            for (int j = 0; j < N; j++) {
                inverted[j][i] = vector[j];
            }
            vector[i] = 0;
        }
        Matrix<double, N, N> res;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                res[i][j] = inverted[i][j];
            }
        }
        return res;
    }

    template<typename T, size_t N>
    Matrix<T, N, N> identity() {
        Matrix<T, N, N> res;
        for (int i = 0; i < N; i++) {
            res[i][i] = 1;
        }
        return res;
    }

}
#endif