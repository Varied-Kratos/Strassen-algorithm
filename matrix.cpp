#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int rws, int cls) : rows(rws), columns(cls), data(rws, std::vector<double>(cls)) {}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(rows, other.columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            double sum = 0;
            for (int k = 0; k < columns; k++) {
                sum += data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

std::vector<Matrix> Matrix::split() const {
    int n = rows / 2;
    std::vector<Matrix> submatrices(4, Matrix(n, n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            submatrices[0].data[i][j] = data[i][j];
            submatrices[1].data[i][j] = data[i][j + n];
            submatrices[2].data[i][j] = data[i + n][j];
            submatrices[3].data[i][j] = data[i + n][j + n];
        }
    }
    
    return submatrices;
}

Matrix Matrix::combine(const Matrix& a11, const Matrix& a12,
                      const Matrix& a21, const Matrix& a22) {
    int n = a11.rows;
    int size = n * 2;
    Matrix result(size, size);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.data[i][j] = a11.data[i][j];
            result.data[i][j + n] = a12.data[i][j];
            result.data[i + n][j] = a21.data[i][j];
            result.data[i + n][j + n] = a22.data[i][j];
        }
    }
    
    return result;
}

void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}