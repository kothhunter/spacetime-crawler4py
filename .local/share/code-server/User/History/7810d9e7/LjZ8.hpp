#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "array.hpp"

template <typename T>
class Matrix {
public:
    Matrix() : rows{0}, cols{0}, data{} {}

    Matrix(int rows, int cols) : rows{rows}, cols{cols}, data(rows) {
        for (int i = 0; i < rows; ++i) {
            data[i] = Array<T>(cols);
        }
    }

    // Get a particular row of the matrix.
    Array<T>& operator[](int row) {
        return data[row];
    }

    const Array<T>& operator[](int row) const {
        return data[row];
    }

    int num_rows() const {
        return rows;
    }

    int num_cols() const {
        return cols;
    }

    void fill(const T& val) {
        for (int i = 0; i < rows; ++i) {
            data[i].fill(val);
        }
    }

    // fill matrix, set entry in row `i` and column `j` to fn(i, j)
    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = fn(i, j);
            }
        }
    }