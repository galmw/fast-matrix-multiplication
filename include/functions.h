// header guard
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<int> row;
typedef std::vector<row> matrix;

matrix standard_mat_mul(const matrix &mat1, const matrix &mat2);

matrix fast_mat_mul(const matrix &mat1, const matrix &mat2);

matrix faster_mat_mul(const matrix &mat1, const matrix &mat2);

matrix random_matrix(int m, int n);

void print_matrix(const matrix &matrix);

bool equal_matrix(const matrix &matrix_a, const matrix &matrix_b);

// end of header guard
#endif