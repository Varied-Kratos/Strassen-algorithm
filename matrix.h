#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int columns;

public:
    Matrix(int rows = 0, int columns = 0, double value = 0.0);
    
    int getRows() const { return rows; }
    int getColumns() const { return columns; }
    
    double get(int i, int j) const;
    void set(int i, int j, double value);
    
    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;
    
    std::vector<Matrix> split() const;
    
    static Matrix combine(const Matrix& a11, const Matrix& a12,
                         const Matrix& a21, const Matrix& a22);
    
    void print() const;
};

#endif // MATRIX_H