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