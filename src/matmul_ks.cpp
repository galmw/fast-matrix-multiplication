#include <iostream>
#include <iomanip>
#include "matrix.h"

// this function transfers a Matrix to the alternative base, in-place
void base_transfer(Matrix &mat) {
	int size = mat.rows() / 2;
	// step 1
	Matrix::add_matrix(mat, mat, mat, -1, size, size, size, 0, size, 0, size);
	// step 2
	Matrix::add_matrix(mat, mat, mat, 1, size, size, 0, size, size, size, size);
	// step 3
	Matrix::add_matrix(mat, mat, mat, 1, 0, size, size, 0, 0, size, size);
}

// this function reverse transfers a Matrix from the alternative base, in-place
void reverse_base_transfer(Matrix &mat) {
	int size = mat.rows() / 2;
	// step 1
	Matrix::add_matrix(mat, mat, mat, -1, size, size, 0, size, size, size, size);
	// step 2
	Matrix::add_matrix(mat, mat, mat, -1, 0, size, size, 0, 0, size, size);
	// step 3
	Matrix::add_matrix(mat, mat, mat, 1, size, size, size, 0, size, size, size);
	// step 4
	Matrix::add_matrix(mat, mat, mat, -1, size, size, size, 0, size, 0, size);
}

/*
// this function receives a Matrix and recursivly transfers its base, in-place
void base_transfer_recursive(Matrix &mat, int row, int col, int size) {
	if (size == 1) {
		return;
	}

	base_transfer(mat);
	base_transfer_recursive(mat, 0, 0, size / 2);
	base_transfer_recursive(mat, 0, size / 2, size / 2);
	base_transfer_recursive(mat, size / 2, 0, size / 2);
	base_transfer_recursive(mat, size / 2, size / 2, size / 2);
}

// this function receives a Matrix and recursivly reverse transfers its base, in-place
void reverse_base_transfer_recursive(Matrix &mat, int row, int col, int size) {
	if (size == 1) {
		return;
	}
 
	reverse_base_transfer(mat);
	reverse_base_transfer_recursive(mat, 0, 0, size / 2);
	reverse_base_transfer_recursive(mat, 0, size / 2, size / 2);
	reverse_base_transfer_recursive(mat, size / 2, 0, size / 2);
	reverse_base_transfer_recursive(mat, size / 2, size / 2, size / 2);
}


void base_transfer_full(Matrix &mat) {
	base_transfer_recursive(mat, 0, 0, mat.size());
}

void reverse_base_transfer_full(Matrix &mat) {
	reverse_base_transfer_recursive(mat, 0, 0, mat.size());
}
*/


// this function multiplies 2 matrices using the fast alternative basis Matrix algorithm
void matmul_ks(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	int col_1 = mat_a.cols();
	int row_2 = mat_b.rows();

	if (col_1 != row_2) {
		std::cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return;
	}

	if (col_1 == 1) {
		result.p[0][0] = mat_a.p[0][0] * mat_b.p[0][0];
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
	base_transfer(mat_a);
	base_transfer(mat_b);
	Matrix::split_matrix(mat_a, a00, a01, a10, a11, size);
	Matrix::split_matrix(mat_b, b00, b01, b10, b11, size);
	reverse_base_transfer(mat_a);
	reverse_base_transfer(mat_b);

	// Allocate sub-matrices
	Matrix m1(split_index, split_index);
	Matrix m2(split_index, split_index);
	Matrix m3(split_index, split_index);
	Matrix m4(split_index, split_index);
	Matrix m5(split_index, split_index);
	Matrix m6(split_index, split_index);
	Matrix m7(split_index, split_index);

	// using ks instead of strassen.
	matmul_ks(m1, a11, b11);
	matmul_ks(m2, a10, b10);
	matmul_ks(m3, a01, b01);
	matmul_ks(m4, a00, b00);

	Matrix temp0(split_index, split_index);
	Matrix temp1(split_index, split_index);
	Matrix::add_matrix(temp0, a01, a10, -1);
	Matrix::add_matrix(temp1, b11, b01, -1);
	matmul_ks(m5, temp0, temp1);

	Matrix::add_matrix(temp0, a01, a00, -1);
	Matrix::add_matrix(temp1, b01, b10, -1);
	matmul_ks(m6, temp0, temp1);

	Matrix::add_matrix(temp0, a11, a01, -1);
	Matrix::add_matrix(temp1, b01, b00, -1);
	matmul_ks(m7, temp0, temp1);
	
	// Allocate sub-matrices
	Matrix result_matrix_00(split_index, split_index);
	Matrix result_matrix_01(split_index, split_index);
	Matrix result_matrix_10(split_index, split_index);
	Matrix result_matrix_11(split_index, split_index);

	// 00
	//Matrix::add_matrix(result, m4, m5, 1, 0, 0, 0, 0, 0, 0, split_index);

	// 01
	//Matrix::add_matrix(result, m3, m5, 1, 0, 0, 0, 0, 0, split_index, split_index);
	//Matrix::add_matrix(result, result, m6, -1, 0, 0, 0, 0, 0, split_index, split_index);	
	//Matrix::add_matrix(result, result, m7, 1, 0, 0, 0, 0, 0, split_index, split_index);

	// 10
	//Matrix::add_matrix(result, m2, m7, 1, 0, 0, 0, 0, split_index, 0, split_index);

	// 11
	//Matrix::add_matrix(result, m1, m6, -1, 0, 0, 0, 0, split_index, split_index, split_index);
	
	
	Matrix::add_matrix(result_matrix_00, m4, m5);

	Matrix::add_matrix(result_matrix_01, m3, m5);
	Matrix::add_matrix(result_matrix_01, result_matrix_01, m6, -1);
	Matrix::add_matrix(result_matrix_01, result_matrix_01, m7);

	Matrix::add_matrix(result_matrix_10, m2, m7);

	Matrix::add_matrix(result_matrix_11, m1, m6, -1);
	// return to standard base
	
	Matrix::merge_matrix(result, result_matrix_00, result_matrix_01, result_matrix_10, result_matrix_11);
	
	reverse_base_transfer(result);
	return;
}
