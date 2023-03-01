#include <iostream>
#include <iomanip>
#include "matrix.h"

// this function transfers a Matrix to the alternative base, in-place
// It performs one step of the base transfer, for the submatrix staring in (i,j), of square size 'size'.
// The minimum expected 'size' is 1.
void base_transfer_step(Matrix &mat, int size, int i=0, int j=0) {
	// step 1: a10 = a11 - a10
	Matrix::add_matrix(mat, mat, mat, -1, i + size, j + size, i + size, j + 0, i + size, j + 0, size);
	// step 2: a11 = a11 + a01
	Matrix::add_matrix(mat, mat, mat, 1, i + size, j + size, i + 0, j + size, i + size, j + size, size);
	// step 3: a01 = a01 + a10
	Matrix::add_matrix(mat, mat, mat, 1, i + 0, j + size, i + size, j + 0, i + 0, j + size, size);
}

// this function reverse transfers a Matrix from the alternative base, in-place.
void reverse_base_transfer_step(Matrix &mat, int size, int i=0, int j=0) {
	// step 1
	Matrix::add_matrix(mat, mat, mat, -1, i + size, j + size, i + 0, j + size, i + size, j + size, size);
	// step 2
	Matrix::add_matrix(mat, mat, mat, -1, i + 0, j + size, i + size, j + 0, i + 0, j + size, size);
	// step 3
	Matrix::add_matrix(mat, mat, mat, 1, i + size, j + size, i + size, j + 0, i + size, j + size, size);
	// step 4
	Matrix::add_matrix(mat, mat, mat, -1, i + size, j + size, i + size, j + 0, i + size, j + 0, size);
}


// this function receives a Matrix and recursivly transfers its base, in-place
void base_transfer_recursive(Matrix &mat, int size, int row=0, int col=0) {
	if (size == 1) {
		return;
	}

	if (size > 2) {
		// Recursively call the function on the 4 submatrices
		base_transfer_recursive(mat, size / 2, row + 0, col + size / 2);
		base_transfer_recursive(mat, size / 2, row + size / 2, col + 0);
		base_transfer_recursive(mat, size / 2, row + size / 2, col + size / 2);
		base_transfer_recursive(mat, size / 2, row + 0, col + 0);
	}

	// Perform 1 step of the base transfer
	base_transfer_step(mat, size / 2, row, col);

}

// this function receives a Matrix and recursivly reverse transfers its base, in-place
void reverse_base_transfer_recursive(Matrix &mat, int size, int row=0, int col=0) {
	if (size == 1) {
		return;
	}
	if (size > 2) {
		// Recursively call the function on the 4 submatrices
		reverse_base_transfer_recursive(mat, size / 2, row + 0, col + size / 2);
		reverse_base_transfer_recursive(mat, size / 2, row + size / 2, col + 0);
		reverse_base_transfer_recursive(mat, size / 2, row + size / 2, col + size / 2);
		reverse_base_transfer_recursive(mat, size / 2, row + 0, col +0);
	}

	// Perform 1 step of the reverse base transfer
	reverse_base_transfer_step(mat, size / 2, row, col);

}


void matmul_ks_inner(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	int col_1 = mat_a.cols();
	int row_2 = mat_b.rows();

	if (col_1 != row_2) {
		std::cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return;
	}

	if (col_1 == 1) {
		result(0,0) = mat_a(0,0) * mat_b(0,0);
		// result.p[0][0] = mat_a.p[0][0] * mat_b.p[0][0];
		return;
	}

	int size = mat_a.rows();
	int split_index = col_1 / 2;

	// Allocate sub-matrices
	Matrix a00(split_index, split_index);
	Matrix a01(split_index, split_index);
	Matrix a10(split_index, split_index);
	Matrix a11(split_index, split_index);
	Matrix b00(split_index, split_index);
	Matrix b01(split_index, split_index);
	Matrix b10(split_index, split_index);
	Matrix b11(split_index, split_index);

	// Splitting matrices A and B into 4 sub-matrices with a base transfer
	Matrix::split_matrix(mat_a, a00, a01, a10, a11, size);
	Matrix::split_matrix(mat_b, b00, b01, b10, b11, size);

	// Allocate sub-matrices
	Matrix m1(split_index, split_index);
	Matrix m2(split_index, split_index);
	Matrix m3(split_index, split_index);
	Matrix m4(split_index, split_index);
	Matrix m5(split_index, split_index);
	Matrix m6(split_index, split_index);
	Matrix m7(split_index, split_index);

	// using ks instead of strassen.
	matmul_ks_inner(m1, a11, b11);
	matmul_ks_inner(m2, a10, b10);
	matmul_ks_inner(m3, a01, b01);
	matmul_ks_inner(m4, a00, b00);

	Matrix temp0(split_index, split_index);
	Matrix temp1(split_index, split_index);
	Matrix::add_matrix(temp0, a01, a10, -1);
	Matrix::add_matrix(temp1, b11, b01, -1);
	matmul_ks_inner(m5, temp0, temp1);

	Matrix::add_matrix(temp0, a01, a00, -1);
	Matrix::add_matrix(temp1, b01, b10, -1);
	matmul_ks_inner(m6, temp0, temp1);

	Matrix::add_matrix(temp0, a11, a01, -1);
	Matrix::add_matrix(temp1, b01, b00, -1);
	matmul_ks_inner(m7, temp0, temp1);
	
	// Calculate the sub-matrices, and fill the result Matrix with the sub-matrices

	// 00
	Matrix::add_matrix(result, m4, m5, 1, 0, 0, 0, 0, 0, 0, split_index);

	// 01
	Matrix::add_matrix(result, m3, m5, 1, 0, 0, 0, 0, 0, split_index, split_index);
	Matrix::add_matrix(result, result, m6, -1, 0, split_index, 0, 0, 0, split_index, split_index);	
	Matrix::add_matrix(result, result, m7, 1, 0, split_index, 0, 0, 0, split_index, split_index);

	// 10
	Matrix::add_matrix(result, m2, m7, 1, 0, 0, 0, 0, split_index, 0, split_index);

	// 11
	Matrix::add_matrix(result, m1, m6, -1, 0, 0, 0, 0, split_index, split_index, split_index);

	return;
}

// this function multiplies 2 matrices using the fast alternative basis Matrix algorithm
void matmul_ks(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	// make sure the matrices are square
	if (mat_a.rows() != mat_a.cols() || mat_b.rows() != mat_b.cols()) {
		std::cout << "\nError: The matrices must be square\n";
		return;
	}

	Matrix new_a(mat_a);
	Matrix new_b(mat_b);

	base_transfer_recursive(new_a, new_a.rows());
	base_transfer_recursive(new_b, new_b.rows());
		
	matmul_ks_inner(result, new_a, new_b);
	reverse_base_transfer_recursive(result, result.rows());
}