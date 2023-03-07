#include "matrix.h"
#include <Accelerate/Accelerate.h>


 void matmul_strassen_inner(Submatrix &result, Submatrix &mat_a, Submatrix &mat_b) {
	int size = mat_a.rows();

	if (size == 1) {
		result(0, 0) = mat_a(0, 0) * mat_b(0, 0);
		return;
	}

	int subsize = size / 2;

	// Allocate sub-matrices
	Submatrix a00(mat_a, 0, 0, subsize, subsize);
	Submatrix a01(mat_a, 0, subsize, subsize, subsize);
	Submatrix a10(mat_a, subsize, 0, subsize, subsize);
	Submatrix a11(mat_a, subsize, subsize, subsize, subsize);

	Submatrix b00(mat_b, 0, 0, subsize, subsize);
	Submatrix b01(mat_b, 0, subsize, subsize, subsize);
	Submatrix b10(mat_b, subsize, 0, subsize, subsize);
	Submatrix b11(mat_b, subsize, subsize, subsize, subsize);

	// Allocate sub-matrices
	Matrix m1(subsize, subsize);
	Matrix m2(subsize, subsize);
	Matrix m3(subsize, subsize);
	Matrix m4(subsize, subsize);
	Matrix m5(subsize, subsize);
	Matrix m6(subsize, subsize);
	Matrix m7(subsize, subsize);

	Matrix temp0(subsize, subsize);

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
	Submatrix r00(result, 0, 0, subsize, subsize);
	Submatrix r01(result, 0, subsize, subsize, subsize);
	Submatrix r10(result, subsize, 0, subsize, subsize);
	Submatrix r11(result, subsize, subsize, subsize, subsize);

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