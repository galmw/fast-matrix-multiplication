// header guard
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<int> row;
typedef std::vector<row> matrix;

matrix create_matrix(int size);

void standard_mat_mul(matrix &result, const matrix &mat1, const matrix &mat2);

void fast_mat_mul(matrix &result, const matrix &matrix_a, const matrix &matrix_b);

void faster_mat_mul(matrix &result, const matrix &matrix_a, const matrix &matrix_b);

matrix random_matrix(int m, int n);

void base_transfer(matrix &matrix);

void print_matrix(const matrix &matrix);

bool equal_matrix(const matrix &matrix_a, const matrix &matrix_b);

// end of header guard
#endif