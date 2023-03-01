#include <iostream>
#include <iomanip>
#include <cmath>
#include "matrix.h"


int phi_matrix[21][9] = {
	{ 0, -1,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0, -1,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  1,  1,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0, -1,  0,  1,  0},
	{-1,  0, -1,  0,  0,  0, -1,  0,  0},
	{ 0,  0,  0,  1, -1,  0,  0,  0,  1},
	{ 0,  0,  0,  0,  0,  0,  1,  0,  0},
	{ 0,  0, -1, -1,  1,  1,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0, -1},
	{ 0,  1,  0, -1,  0,  0,  0,  0,  0},
	{ 0,  0,  0, -1,  0, -1,  0,  0, -1},
	{ 0,  0,  0,  1, -1,  0,  0, -1,  0},
	{ 0,  0,  0,  0,  0, -1, 0,  0,  -1},
	{ 1, -1,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  1,  0},
	{ 0,  0,  0,  1,  0,  0,  0,  0,  0},
	{ 1, -1,  0,  0,  0,  0,  1,  0,  0},
	{ 0,  0,  0,  1, -1,  0,  0,  0,  0},
	{-1,  1,  0,  0,  0,  0, -1,  1,  1},
	{ 0,  0,  0,  0,  1,  0,  0,  1,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  0,  1},
};

int psi_matrix[21][9] = {
	{ 0,  0,  1,  0,  0,  1,  0,  1, -1},
	{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  1,  0,  0,  1,  0,  0,  0},
	{ 0,  0,  0,  0,  0, -1,  0,  1,  0},
	{-1, -1,  1,  0,  0,  0,  0,  0,  0},
	{ 0,  0, -1,  0,  0, -1,  0,  0,  1},
	{ 1,  1,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  1,  0},
	{ 0,  0,  0,  0,  0, -1,  0,  0,  1},
	{ 0,  1,  0,  0,  1,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  0, -1,  1},
	{ 1,  0,  0,  0, -1,  1,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0, -1,  0,  0},
	{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  1,  1, -1,  0,  0,  0},
	{ 0,  1, -1,  0,  1, -1,  0, -1,  1},
	{ 1,  1,  0,  0,  0,  1,  0,  0,  0},
	{ 0,  0,  0,  0, -1,  0,  0,  1,  0},
	{ 0,  0,  0,  0,  0,  1,  0,  0,  0},
	{ 1,  0,  0,  1,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0, -1,  1,  1,  0}
};

int tau_matrix[21][9] = {
	{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  1,  0,  0,  1,  1,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  0,  1, -1,  0},
	{ 0,  0, -1,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  1,  0,  1, -1,  1,  0},
	{ 0,  0, -1,  0,  0,  0,  0,  0,  1},
	{ 0,  1,  1,  0,  1,  1,  0,  0,  0},
	{ 0, -1, -1,  0,  0,  0,  0,  1,  1},
	{ 0,  0,  0,  0,  1,  1,  0,  0,  0},
	{ 0,  0,  0,  0,  0,  1,  0,  0, -1},
	{ 0,  1,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  0,  0, -1,  0,  0,  0},
	{ 0,  0,  0,  1,  0,  0, -1,  1,  0},
	{ 1, -1,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  0, -1,  0,  0,  1,  0,  0},
	{ 0,  1,  0,  0,  1,  0,  0,  0,  0},
	{ 0,  0, -1,  0,  0,  0,  0,  1,  1},
	{ 0,  0,  0, -1,  1,  0,  1, -1,  0},
	{ 0,  0,  0,  0,  0,  0,  0,  1,  1},
	{ 0,  0,  0,  1,  0,  0,  0,  0,  0},
	{ 0,  0,  0, -1,  0,  0,  1,  0,  0},

};

void base_transfer(Matrix &mat, Matrix &result) {

}

// this function receives a 1-dim index from 0 to 8 and returns the 2-dim index
void get3_2d_index(int index, int &i, int &j) {
	i = index / 3;
	j = index % 3;
}

// this function receives a 2-dim index and returns the 1-dim index
int get3_1d_index(int i, int j) {
	return i * 3 + j;
}

// this function receives a 1-dim index from 0 to 20 and returns the 2-dim index
void get7_2d_index(int index, int &i, int &j) {
	i = index / 7;
	j = index % 7;
}

// this function receives a 2-dim index and returns the 1-dim index
int get7_1d_index(int i, int j) {
	return i * 7 + j;
}

// this function receives a Matrix in the standard basis, 3n * 3n is allocated, the full size is 3n * 7n., allocated in the powers of 3, and transfers it into a matrix in the new dimension.
// It performs one step of the base transfer, for the submatrix staring in (i,j), of square size 'size'.
// The minimum expected 'size' is 3.
void base_dim_transfer_step(Matrix &mat, int size, int transfer_matrix[21][9]) {
	int subsize = size / 3;

	// orig contains the originial dimension of the content.
	Matrix orig(mat.rows(), mat.rows());

	// copy the contents of mat into orig
	for (int i = 0; i < orig.rows(); i++) {
		for (int j = 0; j < orig.cols(); j++) {
			orig(i, j) = mat(i, j);
		}
	}
	// clear out the content of mat
	for (int i = 0; i < mat.rows(); i++) {
		for (int j = 0; j < mat.cols(); j++) {
			mat(i, j) = 0;
		}
	}
	// do the base transfer from orig to mat8
	int orig_i, orig_j, target_i, target_j;
	for (int target_index = 0; target_index < 21; target_index++) {	
		get7_2d_index(target_index, target_i, target_j);
		// for each entry in the target matrix, add the appropriate submatrices from the original matrix
		for (int orig_index = 0; orig_index < 9; orig_index++) {		
			if (transfer_matrix[target_index][orig_index] != 0) {
				get3_2d_index(orig_index, orig_i, orig_j);
				Matrix::add_matrix(mat, mat, orig, transfer_matrix[target_index][orig_index],
					target_i * subsize, target_j * subsize, orig_i * subsize, orig_j * subsize, target_i * subsize, target_j * subsize, subsize);
			}
		}
	}
}

void matmul_sparse_inner(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	int size = mat_a.rows();

	if (size == 1) {
		result(0, 0) = mat_a(0, 0) * mat_b(0, 0);
		return;
	}

	int split_index = size / 3;
	// Allocate 23 matrices named from m1 to m23
	Matrix m1(split_index, split_index);
	Matrix m2(split_index, split_index);
	Matrix m3(split_index, split_index);
	Matrix m4(split_index, split_index);
	Matrix m5(split_index, split_index);
	Matrix m6(split_index, split_index);
	Matrix m7(split_index, split_index);
	Matrix m8(split_index, split_index);
	Matrix m9(split_index, split_index);
	Matrix m10(split_index, split_index);
	Matrix m11(split_index, split_index);
	Matrix m12(split_index, split_index);
	Matrix m13(split_index, split_index);
	Matrix m14(split_index, split_index);
	Matrix m15(split_index, split_index);
	Matrix m16(split_index, split_index);
	Matrix m17(split_index, split_index);
	Matrix m18(split_index, split_index);
	Matrix m19(split_index, split_index);
	Matrix m20(split_index, split_index);
	Matrix m21(split_index, split_index);
	Matrix m22(split_index, split_index);
	Matrix m23(split_index, split_index);

	int a_i, a_j, b_i, b_j;
	get7_2d_index(0, a_i, a_j);
	get7_2d_index(19, b_i, b_j);


	//Matrix::add_matrix(m1, )
	//matmul_sparse_inner(m1, mat_a, mat_b, a_i, a_j, b_i, b_j, 0, 0, split_index, split_index, split_index);
	return;
}

// this function multiplies 2 matrices using the fast sparse alternative basis Matrix algorithm
void matmul_sparse(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	// make sure the matrices are square
	if (mat_a.rows() != mat_a.cols() || mat_b.rows() != mat_b.cols()) {
		std::cout << "\nError: The matrices must be square\n";
		return;
	}
	int new_size = mat_a.rows();
	// calculate the log in base 3 of new_size
	int log3 = 0;
	while (new_size > 1) {
		new_size /= 3;
		log3++;
	}

	// create a new matrix who's number of columns is 7 to the power of log3.
	Matrix new_a(mat_a.rows(), (int)pow(7, log3));
	Matrix new_b(mat_a.rows(), (int)pow(7, log3));

	// copy the matrices to the new matrices
	for (int i = 0; i < mat_a.rows(); i++) {
		for (int j = 0; j < mat_a.cols(); j++) {
			new_a(i, j) = mat_a(i, j);
			new_b(i, j) = mat_b(i, j);
		}
	}

	// this should be a different thansfer for a and b.
	base_dim_transfer_step(new_a, mat_a.rows(), phi_matrix);
	base_dim_transfer_step(new_b, mat_b.rows(), psi_matrix);
	//base_transfer(mat_a, new_a);
	//base_transfer(mat_b, new_b);
	//base_transfer_recursive(new_a, log3);
	//// base_transfer_recursive(new_b, log3);

	matmul_sparse_inner(result, mat_a, mat_b);

	
	// reverse_base_transfer_recursive(result, log3);

}