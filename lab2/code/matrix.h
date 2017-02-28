#ifndef MATRIX_H
#define MATRIX_H

#include <c++/cstdlib>
#include <c++/ostream>

using namespace std;

template<typename T>
class Matrix {
public:
    Matrix(int n) : Matrix(n, n) {}

    Matrix(int n, int m) {
        this->n = n;
        this->m = m;
        values = new T *[n];
        for (int i = 0; i < n; ++i) {
            values[i] = new T[m];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                values[i][j] = 0;
            }
        }
    }

    Matrix(int n, int m, T *values[]) {
        this->n = n;
        this->m = m;
        this->values = new T *[n];
        for (int i = 0; i < n; ++i) {
            this->values[i] = new T[m];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                this->values[i][j] = values[i][j];
            }
        }
    }

    T const *operator[](int i) const {
        return &values[i][0];
    }

    T *operator[](int i) {
        return &values[i][0];
    }

    Matrix invert() {
        return *this;
    }

    T norm() {
        T max = 0.0;
        for (int i = 0; i < n; i++) {
            T sum = 0.0;
            for (int j = 0; j < m; j++) {
                sum += abs(values[i][j]);
            }
            max = sum > max ? sum : max;
        }
        return max;
    }

    Matrix &operator+(Matrix another) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                values[i][j] += another.values[i][j];
            }
        }
        return *this;
    }

    Matrix &operator-(Matrix another) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                values[i][j] -= another.values[i][j];
            }
        }
        return *this;
    }

    Matrix &operator*(int k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                values[i][j] *= k;
            }
        }
        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < n; ++i) {
            free(values[i]);
        }
        free(values);
    }

    T abs(T value) {
        return value >= 0 ? value : -value;
    }

    friend ostream &operator<<(ostream &os, Matrix &matrix) {
        for (int i = 0; i < matrix.n; ++i) {
            for (int j = 0; j < matrix.m; ++j) {
                os << matrix.values[i][j] << "\t";
            }
            os << '\n';
        }
        return os;
    }

private:
    int n;
    int m;
    T **values;

};

#endif // MATRIX_H
