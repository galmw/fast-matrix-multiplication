#include <iostream>
#include <iomanip>
#include "matrix.h"

void matmul_sparse_inner(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	return;
}

// this function multiplies 2 matrices using the fast sparse alternative basis Matrix algorithm
void matmul_sparse(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	// make sure the matrices are square
	if (mat_a.rows() != mat_a.cols() || mat_b.rows() != mat_b.cols()) {
		std::cout << "\nError: The matrices must be square\n";
		return;
	}
}