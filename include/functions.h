// header guard
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<int> row;
typedef std::vector<row> matrix;

matrix standard_mat_mul(matrix mat1, matrix mat2);

matrix fast_mat_mul(matrix mat1, matrix mat2);

matrix faster_mat_mul(matrix mat1, matrix mat2);

matrix random_matrix(int m, int n);

void print_matrix(matrix &matrix);

bool equal_matrix(matrix matrix_a, matrix matrix_b);

// end of header guard
#endif