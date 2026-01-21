#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
class Matrix {
public:
    std::vector<std::vector<double>> data;
    int rows;
    int columns;

    Matrix(int rows = 0, int columns = 0);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    std::vector<Matrix> split() const;

    static Matrix combine(const Matrix& a11, const Matrix& a12,
                         const Matrix& a21, const Matrix& a22);

    void print() const;
    
    void load(const std::string& filename);

    void save(const std::string& filename) const;
};

#endif