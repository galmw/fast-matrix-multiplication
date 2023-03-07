#include "matrix.h"
#include <Accelerate/Accelerate.h>


 void matmul_strassen_inner(Submatrix &result, Submatrix &mat_a, Submatrix &mat_b,
        int a_i = 0, int a_j = 0, int b_i = 0, int b_j = 0, int c_i = 0, int c_j = 0, int size = 0) {
    if (size == 0) {
		size = mat_a.rows();
	}
	if (size == 1) {
		result(c_i, c_j) = mat_a(a_i, a_j) * mat_b(b_i, b_j);
		return;
	}

	int split_index = size / 2;

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

	Matrix temp0(split_index, split_index);

	Matrix::add_matrix(m1, b01, b11, -1);
	matmul_strassen_inner(m1, a00, m1);

	Matrix::add_matrix(m2, a00, a01);
	matmul_strassen_inner(m2, m2, b11);

	Matrix::add_matrix(m3, a10, a11);
	matmul_strassen_inner(m3, m3, b00);
	
	Matrix::add_matrix(m4, b10, b00, -1);
	matmul_strassen_inner(m4, a11, m4);
	
	Matrix::add_matrix(temp0, a00, a11);
	Matrix::add_matrix(m5, b00, b11);
	matmul_strassen_inner(m5, temp0, m5);
	
	Matrix::add_matrix(temp0, a01, a11, -1);
	Matrix::add_matrix(m6, b10, b11);
	matmul_strassen_inner(m6, temp0, m6);

	Matrix::add_matrix(temp0, a00, a10, -1);
	Matrix::add_matrix(m7, b00, b01);
	matmul_strassen_inner(m7, temp0, m7);
	
	// Calculate the sub-matrices, and fill the result Matrix with the sub-matrices
	Submatrix r00(result, 0, 0, split_index, split_index);
	Submatrix r01(result, 0, split_index, split_index, split_index);
	Submatrix r10(result, split_index, 0, split_index, split_index);
	Submatrix r11(result, split_index, split_index, split_index, split_index);

    // 00
    Matrix::add_matrix(r00, m5, m4);
    Matrix::add_matrix(r00, r00, m6);
	Matrix::add_matrix(r00, r00, m2, -1);

    // 01
	Matrix::add_matrix(r01, m1, m2);

    // 10
	Matrix::add_matrix(r10, m3, m4);

    // 11
	Matrix::add_matrix(r11, m5, m1);
	Matrix::add_matrix(r11, r11, m3, -1);
	Matrix::add_matrix(r11, r11, m7, -1);
	return;
 }


// this function multiplies 2 matrices using the Strassen algorithm
void matmul_strassen(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
    matmul_strassen_inner(result, mat_a, mat_b);
}