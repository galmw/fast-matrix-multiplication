#include <iostream>
#include <iomanip>
#include "matrix.h"

// this function transfers a Matrix to the alternative base, in-place
// It performs one step of the base transfer, for the submatrix staring in (i,j), of square size 'size'.
// The minimum expected 'size' is 1.
void base_transfer_step(Submatrix &mat) {
	int subsize = mat.rows() / 2;
	Submatrix a01(mat, 0, subsize, subsize, subsize);
	Submatrix a10(mat, subsize, 0, subsize, subsize);
	Submatrix a11(mat, subsize, subsize, subsize, subsize);	
	// step 1
	Matrix::add_matrix(a10, a11, a10, -1);
	// step 2
	Matrix::add_matrix(a11, a11, a01);
	// step 3
	Matrix::add_matrix(a01, a01, a10);
}

// this function reverse transfers a Matrix from the alternative base, in-place.
void reverse_base_transfer_step(Submatrix &mat) {
	int subsize = mat.rows() / 2;
	Submatrix a01(mat, 0, subsize, subsize, subsize);
	Submatrix a10(mat, subsize, 0, subsize, subsize);
	Submatrix a11(mat, subsize, subsize, subsize, subsize);
	// step 1
	Matrix::add_matrix(a11, a11, a01, -1);
	// step 2
	Matrix::add_matrix(a01, a01, a10, -1);
	// step 3
	Matrix::add_matrix(a11, a11, a10);
	// step 4
	Matrix::add_matrix(a10, a11, a10, -1);
}

// this function receives a Matrix and recursivly transfers its base, in-place
void base_transfer_recursive(Submatrix &mat) {
	int size = mat.rows();
	if (size == 1) {
		return;
	}

	// Perform 1 step of the base transfer
	base_transfer_step(mat);

	if (size > 2) {
		int subsize = mat.rows() / 2;
		Submatrix a00(mat, 0, 0, subsize, subsize);
		Submatrix a01(mat, 0, subsize, subsize,subsize);
		Submatrix a10(mat, subsize, 0, subsize, subsize);
		Submatrix a11(mat, subsize, subsize, subsize, subsize);

		// Recursively call the function on the 4 submatrices
		base_transfer_recursive(a00);
		base_transfer_recursive(a01);
		base_transfer_recursive(a10);
		base_transfer_recursive(a11);
	}
}

// this function receives a Matrix and recursivly reverse transfers its base, in-place
void reverse_base_transfer_recursive(Submatrix &mat) {
	int size = mat.rows();
	if (size == 1) {
		return;
	}
	if (size > 2) {
		int subsize = mat.rows() / 2;

		Submatrix a00(mat, 0, 0, subsize, subsize);
		Submatrix a01(mat, 0, subsize, subsize,subsize);
		Submatrix a10(mat, subsize, 0, subsize, subsize);
		Submatrix a11(mat, subsize, subsize, subsize, subsize);
		// Recursively call the function on the 4 submatrices
		reverse_base_transfer_recursive(a00);
		reverse_base_transfer_recursive(a01);
		reverse_base_transfer_recursive(a10);
		reverse_base_transfer_recursive(a11);
	}

	// Perform 1 step of the reverse base transfer
	reverse_base_transfer_step(mat);

}


void matmul_ks_inner(Submatrix &result, Submatrix &mat_a, Submatrix &mat_b) {
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

	int split_index = col_1 / 2;

	// Allocate sub-matrices
	Submatrix a00(mat_a, 0, 0, split_index, split_index);
	Submatrix a01(mat_a, 0, split_index, split_index, split_index);
	Submatrix a10(mat_a, split_index, 0, split_index, split_index);
	Submatrix a11(mat_a, split_index, split_index, split_index, split_index);

	Submatrix b00(mat_b, 0, 0, split_index, split_index);
	Submatrix b01(mat_b, 0, split_index, split_index, split_index);
	Submatrix b10(mat_b, split_index, 0, split_index, split_index);
	Submatrix b11(mat_b, split_index, split_index, split_index, split_index);

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
	Submatrix r00(result, 0, 0, split_index, split_index);
	Submatrix r01(result, 0, split_index, split_index, split_index);
	Submatrix r10(result, split_index, 0, split_index, split_index);
	Submatrix r11(result, split_index, split_index, split_index, split_index);

	// TODO with this new logic we can maybe avoid m1-m7 all together by adding things directly to rXY
	// 00
	Matrix::add_matrix(r00, m4, m5);

	// 01
	Matrix::add_matrix(r01, m3, m5);
	Matrix::add_matrix(r01, r01, m6, -1);	
	Matrix::add_matrix(r01, r01, m7);

	// 10
	Matrix::add_matrix(r10, m2, m7);

	// 11
	Matrix::add_matrix(r11, m1, m6, -1);
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

	base_transfer_recursive(new_a);
	base_transfer_recursive(new_b);
		
	matmul_ks_inner(result, new_a, new_b);
	reverse_base_transfer_recursive(result);
}