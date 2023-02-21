#include "matrix.h"
#include <Accelerate/Accelerate.h>


 void matmul_strassen_inner(Matrix &result, Matrix &mat_a, Matrix &mat_b,
        int a_i = 0, int a_j = 0, int b_i = 0, int b_j = 0, int c_i = 0, int c_j = 0, int size = 0) {
    if (size == 0) {
		size = mat_a.rows();
	}
	if (size == 1) {
		result.p[0][0] = mat_a.p[0][0] * mat_b.p[0][0];
		return;
	}

	int split_index = size / 2;

	// Allocate sub-matrices
	Matrix a00(split_index, split_index);
	Matrix a01(split_index, split_index);
	Matrix a10(split_index, split_index);
	Matrix a11(split_index, split_index);
	Matrix b00(split_index, split_index);
	Matrix b01(split_index, split_index);
	Matrix b10(split_index, split_index);
	Matrix b11(split_index, split_index);

	// Splitting matrices A and B into 4 sub-matrices
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

	Matrix temp0(split_index, split_index);

	Matrix::add_matrix(temp0, b01, b11, -1);
	matmul_strassen(m1, a00, temp0);

	Matrix::add_matrix(temp0, a00, a01);
	matmul_strassen(m2, temp0, b11);

	Matrix::add_matrix(temp0, a10, a11);
	matmul_strassen(m3, temp0, b00);
	
	Matrix::add_matrix(temp0, b10, b00, -1);
	matmul_strassen(m4, a11, temp0);
	
	Matrix temp1(split_index, split_index);
	Matrix::add_matrix(temp0, a00, a11);
	Matrix::add_matrix(temp1, b00, b11);
	matmul_strassen(m5, temp0, temp1);
	
	Matrix::add_matrix(temp0, a01, a11, -1);
	Matrix::add_matrix(temp1, b10, b11);
	matmul_strassen(m6, temp0, temp1);

	Matrix::add_matrix(temp0, a00, a10, -1);
	Matrix::add_matrix(temp1, b00, b01);
	matmul_strassen(m7, temp0, temp1);
	
	// Allocate sub-matrices
	Matrix result_matrix_00(split_index, split_index);
	Matrix result_matrix_01(split_index, split_index);
	Matrix result_matrix_10(split_index, split_index);
	Matrix result_matrix_11(split_index, split_index);

	// Calculate the sub-matrices
	Matrix::add_matrix(result_matrix_00, m5, m4);
	Matrix::add_matrix(result_matrix_00, result_matrix_00, m6);
	Matrix::add_matrix(result_matrix_00, result_matrix_00, m2, -1);

	Matrix::add_matrix(result_matrix_01, m1, m2);
	Matrix::add_matrix(result_matrix_10, m3, m4);

	Matrix::add_matrix(result_matrix_11, m5, m1);
	Matrix::add_matrix(result_matrix_11, result_matrix_11, m3, -1);
	Matrix::add_matrix(result_matrix_11, result_matrix_11, m7, -1);

	// Fill the result Matrix with the sub-matrices
	Matrix::merge_matrix(result, result_matrix_00, result_matrix_01, result_matrix_10, result_matrix_11);
	return;
 }


// this function multiplies 2 matrices using the Strassen algorithm
void matmul_strassen(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
    matmul_strassen_inner(result, mat_a, mat_b, mat_a.rows(), 0, 0);
}