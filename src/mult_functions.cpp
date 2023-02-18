#include <iostream>
#include <iomanip>
#include "matrix.h"
#include <Accelerate/Accelerate.h>


// This function takes as input two matrices and a refernce to output Matrix, and multiplies them using dgemm
void dgemm(Matrix& result, Matrix& mat_a, Matrix& mat_b)
{
    double alpha = 1.0;
    double beta = 0.0;
    int m = mat_a.rows();
    int n = mat_b.cols();
    int k = mat_a.cols();

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, mat_a.arr, k, mat_b.arr, n, beta, result.arr, n);
}

void standard_mat_mul(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
    for (int i = 0; i < mat_a.rows(); i++) {
        for (int j = 0; j < mat_b.cols(); j++) {
            result.p[i][j] = 0;
            for (int k = 0; k < mat_a.cols(); k++) {
                result.p[i][j] += mat_a.p[i][k] * mat_b.p[k][j];
            }
         }
    }
	return;
}

// this function multiplies 2 matrices using the Strassen algorithm
void strassen(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	if (mat_a.rows() == 1) {
		result.p[0][0] = mat_a.p[0][0] * mat_b.p[0][0];
		return;
	}
	
	int size = mat_a.rows();
	int split_index = size / 2;

	// Allocate sub-matrices
	Matrix a00 = Matrix(split_index, split_index);
	Matrix a01 = Matrix(split_index, split_index);
	Matrix a10 = Matrix(split_index, split_index);
	Matrix a11 = Matrix(split_index, split_index);
	Matrix b00 = Matrix(split_index, split_index);
	Matrix b01 = Matrix(split_index, split_index);
	Matrix b10 = Matrix(split_index, split_index);
	Matrix b11 = Matrix(split_index, split_index);

	// Splitting matrices A and B into 4 sub-matrices
	Matrix::split_matrix(mat_a, a00, a01, a10, a11, size);
	Matrix::split_matrix(mat_b, b00, b01, b10, b11, size);

	// Allocate sub-matrices
	Matrix m1 = Matrix(split_index, split_index);
	Matrix m2 = Matrix(split_index, split_index);
	Matrix m3 = Matrix(split_index, split_index);
	Matrix m4 = Matrix(split_index, split_index);
	Matrix m5 = Matrix(split_index, split_index);
	Matrix m6 = Matrix(split_index, split_index);
	Matrix m7 = Matrix(split_index, split_index);

	Matrix temp0 = Matrix(split_index, split_index);

	Matrix::add_matrix(temp0, b01, b11, -1);
	strassen(m1, a00, temp0);

	Matrix::add_matrix(temp0, a00, a01);
	strassen(m2, temp0, b11);

	Matrix::add_matrix(temp0, a10, a11);
	strassen(m3, temp0, b00);
	
	Matrix::add_matrix(temp0, b10, b00, -1);
	strassen(m4, a11, temp0);
	
	Matrix temp1 = Matrix(split_index, split_index);
	Matrix::add_matrix(temp0, a00, a11);
	Matrix::add_matrix(temp1, b00, b11);
	strassen(m5, temp0, temp1);
	
	Matrix::add_matrix(temp0, a01, a11, -1);
	Matrix::add_matrix(temp1, b10, b11);
	strassen(m6, temp0, temp1);

	Matrix::add_matrix(temp0, a00, a10, -1);
	Matrix::add_matrix(temp1, b00, b01);
	strassen(m7, temp0, temp1);
	
	// Allocate sub-matrices
	Matrix result_matrix_00 = Matrix(split_index, split_index);
	Matrix result_matrix_01 = Matrix(split_index, split_index);
	Matrix result_matrix_10 = Matrix(split_index, split_index);
	Matrix result_matrix_11 = Matrix(split_index, split_index);

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

/*


// this function recieves a Matrix and returns 4 sub-matrices, after a base transfer
// this can be done on one big Matrix, in-place. TODO
void split_matrix_and_base_transfer(const Matrix &mat, Matrix &a00, Matrix &a01, Matrix &a10, Matrix &a11, int size) {
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			a00[i][j] = mat[i][j];
			a01[i][j] = mat[i][j + size] - mat[i + size][j] + mat[i + size][j + size];
			a10[i][j] = mat[i + size][j + size] - mat[i + size][j];
			a11[i][j] = mat[i][j + size] + mat[i + size][j + size];
		}
	}
}

// this function transfers a Matrix to the alternative base, in-place
void base_transfer(Matrix &mat, int size) {
	// step 1
	Matrix::add_matrix(mat, mat, mat, -1, size, size, size, 0, size, 0, size);
	// step 2
	Matrix::add_matrix(mat, mat, mat, 1, size, size, 0, size, size, size, size);
	// step 3
	Matrix::add_matrix(mat, mat, mat, 1, 0, size, size, 0, 0, size, size);
}

// this function reverse transfers a Matrix from the alternative base, in-place
void reverse_base_transfer(Matrix &mat, int size) {
	// step 1
	Matrix::add_matrix(mat, mat, mat, -1, size, size, 0, size, size, size, size);
	// step 2
	Matrix::add_matrix(mat, mat, mat, -1, 0, size, size, 0, 0, size, size);
	// step 3
	Matrix::add_matrix(mat, mat, mat, 1, size, size, size, 0, size, size, size);
	// step 4
	Matrix::add_matrix(mat, mat, mat, -1, size, size, size, 0, size, 0, size);
}


// this function recieves 4 sub-matrices and returns a Matrix after a reverse base transfer
void merge_matrix_and_reverse_base_transfer(Matrix &result,
		const Matrix &a00, const Matrix &a01, const Matrix &a10, const Matrix &a11, int size) {

	// Fill the result Matrix with the sub-matrices with a base transfer
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			result[i][j] = a00[i][j];
			result[i][j + size] = a01[i][j] - a10[i][j];
			result[size + i][j] = a11[i][j] - a01[i][j];
			result[i + size][j + size] = a10[i][j] - a01[i][j] + a11[i][j];
		}
	}
}

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

// this function multiplies 2 matrices using the fast alternative basis Matrix algorithm
void faster_mat_mul(Matrix &result, Matrix &matrix_a, Matrix &matrix_b) {
	int col_1 = matrix_a[0].size();
	int row_2 = matrix_b.size();

	if (col_1 != row_2) {
		std::cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return;
	}

	if (col_1 == 1) {
		result[0][0] = matrix_a[0][0] * matrix_b[0][0];
		return;
	}

	int split_index = col_1 / 2;

	// Allocate sub-matrices
	Matrix a00 = create_matrix(split_index);
	Matrix a01 = create_matrix(split_index);
	Matrix a10 = create_matrix(split_index);
	Matrix a11 = create_matrix(split_index);
	Matrix b00 = create_matrix(split_index);
	Matrix b01 = create_matrix(split_index);
	Matrix b10 = create_matrix(split_index);
	Matrix b11 = create_matrix(split_index);

	// Splitting matrices A and B into 4 sub-matrices with a base transfer
	base_transfer(matrix_a);
	base_transfer(matrix_b);
	split_matrix(matrix_a, a00, a01, a10, a11);
	split_matrix(matrix_b, b00, b01, b10, b11);
	reverse_base_transfer(matrix_a);
	reverse_base_transfer(matrix_b);

	// Allocate sub-matrices
	Matrix m1 = create_matrix(split_index);
	Matrix m2 = create_matrix(split_index);
	Matrix m3 = create_matrix(split_index);
	Matrix m4 = create_matrix(split_index);
	Matrix m5 = create_matrix(split_index);
	Matrix m6 = create_matrix(split_index);
	Matrix m7 = create_matrix(split_index);

	// using faster_mat_mul instead of fast.
	faster_mat_mul(m1, a11, b11);
	faster_mat_mul(m2, a10, b10);
	faster_mat_mul(m3, a01, b01);
	faster_mat_mul(m4, a00, b00);

	Matrix temp0 = create_matrix(split_index);
	Matrix temp1 = create_matrix(split_index);
	Matrix::add_matrix(temp0, a01, a10, -1);
	Matrix::add_matrix(temp1, b11, b01, -1);
	faster_mat_mul(m5, temp0, temp1);

	Matrix::add_matrix(temp0, a01, a00, -1);
	Matrix::add_matrix(temp1, b01, b10, -1);
	faster_mat_mul(m6, temp0, temp1);

	Matrix::add_matrix(temp0, a11, a01, -1);
	Matrix::add_matrix(temp1, b01, b00, -1);
	faster_mat_mul(m7, temp0, temp1);
	
	// Allocate sub-matrices (this can be avoided)
	Matrix result_matrix_00 = create_matrix(split_index);
	Matrix result_matrix_01 = create_matrix(split_index);
	Matrix result_matrix_10 = create_matrix(split_index);
	Matrix result_matrix_11 = create_matrix(split_index);

	
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
	
	merge_matrix(result, result_matrix_00, result_matrix_01, result_matrix_10, result_matrix_11);
	
	reverse_base_transfer(result);
	return;
}

// this function returns a random Matrix with the given size
Matrix random_matrix(int m, int n) {
	Matrix result(m, row(n, 0));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			result[i][j] = arc4random() % 10;
		}
	}
	return result;
}



*/
