// header guard
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<int> row;
typedef std::vector<row> matrix;

matrix standardMatMul(matrix mat1, matrix mat2);

void print_matrix(std::string display, matrix matrix,
		int start_row, int start_column, int end_row,
		int end_column);

// end of header guard
#endif