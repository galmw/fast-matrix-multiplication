#include <iostream>
#include <iomanip>
#include <cmath>
#include "matrix.h"


int phi_matrix[21][9] = {
	{ 0, -1,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  0, -1,  0,  0,  0,  0,  0,  0},
	{ 0,  0,  1,  1,  0,  0,  0,  0,  0},
	{ 0,  0,  0,  1, -1,  0,  1, -1,  0},
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

int u_multiply[23] = {0, 1, 2, 3, 4, 5, 6, 1, 13, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
int v_multiply[23] = {19, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
int w_add[23] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 19, 13, 14, 15, 16, 17, 18, 19, 20};

// this function receives a 1-dim index from 0 to 8 and returns the 2-dim index
inline void get3_2d_index(int index, int &i, int &j) {
	i = index / 3;
	j = index % 3;
}

// this function receives a 2-dim index and returns the 1-dim index
inline int get3_1d_index(int i, int j) {
	return i * 3 + j;
}

// this function receives a 1-dim index from 0 to 20 and returns the 2-dim index
inline void get7_2d_index(int index, int &i, int &j) {
	i = index / 7;
	j = index % 7;
}

// this function receives a 2-dim index and returns the 1-dim index
inline int get7_1d_index(int i, int j) {
	return i * 7 + j;
}

int log3(int x) { 
	int log3 = 0;
	// calculate the log in base 3 of x
	int res = x;
	while (res > 1) {
		res /= 3;
		log3++;
	}
	return log3;
}

int pow_3to7(int x) {
	return (int) pow(7, log3(x));
}

// this function receives a Matrix in the standard basis, 3n * 3n is allocated, the full size is 3n * 7n., allocated in the powers of 3, and transfers it into a matrix in the new dimension.
// It performs one step of the base transfer, for the submatrix staring in (i,j), of square size 'size'.
// The minimum expected 'size' is 3.
// TODO - make this so it can also expect just a submatrix.
void base_dim_transfer_step(Matrix &mat, int size, int transfer_matrix[21][9], int row, int col) {
	if (size < 3) {
		std::cout << "Error!" << std::endl;
		return;
	}
	int subsize = size / 3;
	int col_subsize = pow_3to7(subsize);

	// orig contains the originial dimension of the content.
	Matrix orig(size, size);

	// copy the contents of mat into orig
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			orig(i, j) = mat(row + i, col + j);
		}
	}
	// clear out the content of the destined part of mat
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < col_subsize * 7; j++) {
			mat(row + i, col + j) = 0;
		}
	}

	// do the base transfer from orig to mat.
	// important - mat's colmuns needs to be filled with the appropiate gaps to allow further recursive calls.
	int orig_i, orig_j, target_i, target_j;

	for (int target_index = 0; target_index < 21; target_index++) {	
		get7_2d_index(target_index, target_i, target_j);
		// for each entry in the target matrix, add the appropriate subsize*subsize submatrices from the original matrix
		int dest_i = row + target_i * subsize;
		int dest_j = col + target_j *  col_subsize;
		for (int orig_index = 0; orig_index < 9; orig_index++) {		
			if (transfer_matrix[target_index][orig_index] != 0) {
				get3_2d_index(orig_index, orig_i, orig_j);
				Matrix::add_matrix(mat, mat, orig, transfer_matrix[target_index][orig_index],
					dest_i, dest_j, orig_i * subsize, orig_j * subsize, dest_i, dest_j, subsize);
			}
		}
	}
}

// this function receives a Matrix in the transfered basis, 3n * 7n is allocated, the full size is 3n * 7n,
// allocated in the powers of 3, and transfers it into a matrix in the original dimension.
// It performs one step of the base transfer, for the submatrix staring in (i,j), of square size 'size'.
// The minimum expected 'size' is 3.
void base_dim_reverse_transfer_step(Matrix &mat, int size, int row, int col) {
	if (size < 3) {
		std::cout << "Error!" << std::endl;
		return;
	}
	int subsize = size / 3;
	int col_subsize = pow_3to7(subsize);

	// orig contains the originial dimension of the content.
	Matrix orig(size, col_subsize * 7);

	// copy the contents of mat into orig
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < col_subsize * 7; j++) {
			orig(i, j) = mat(row + i, col + j);
		}
	}
	// clear out the content of the destined part of mat
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < col_subsize * 7; j++) {
			mat(row + i, col + j) = 0;
		}
	}

	// do the base transfer from orig to mat
	int orig_i, orig_j, target_i, target_j;

	for (int target_index = 0; target_index < 9; target_index++) {	
		get3_2d_index(target_index, target_i, target_j);

		int dest_i = row + target_i * subsize;
		int dest_j = col + target_j * subsize; // bring the columns back together. TODO think about this.

		// for each entry in the target matrix, add the appropriate subsize*subsize (already reverse transfered to square) submatrices from the original matrix
		for (int orig_index = 0; orig_index < 21; orig_index++) {		
			if (tau_matrix[orig_index][target_index] != 0) {
				get7_2d_index(orig_index, orig_i, orig_j);
				Matrix::add_matrix(mat, mat, orig, tau_matrix[orig_index][target_index],
					dest_i, dest_j, orig_i * subsize, orig_j * col_subsize, dest_i, dest_j, subsize);
			}
		}
	}
}

// this function receives a Matrix in the standard basis, 3^n * 3^n is allocated, the full size is 3^n * 7^n,
// and transfers it recusively into a matrix in the new dimension.
void base_dim_transfer_recursive(Matrix &mat, int size, int transfer_matrix[21][9], int row=0, int col=0) {
	if (size < 3) { 
		return;
	}

	base_dim_transfer_step(mat, size, transfer_matrix, row, col);
	if (size > 3) {
		int subsize = size / 3;
		int col_subsize = pow_3to7(subsize);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				base_dim_transfer_recursive(mat, subsize, transfer_matrix, i * subsize, j * col_subsize);
			}
		}
	}
}

void base_dim_reverse_transfer_recursive(Matrix &mat, int size, int row=0, int col=0) {
	if (size < 3) { 
		return;
	}

	if (size > 3) {
		int subsize = size / 3;
		int col_subsize = pow_3to7(subsize);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				base_dim_reverse_transfer_recursive(mat, subsize, i * subsize, j * col_subsize);
			}
		}
	}
	base_dim_reverse_transfer_step(mat, size, row, col);
}

void matmul_sparse_inner(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	int size = mat_a.rows();

	if (size == 1) {
		result(0, 0) = mat_a(0, 0) * mat_b(0, 0);
		return;
	}

	int subsize = size / 3;
	// TODO make all column references from subsize to col_subsize
	// TODO!! make sure add_matrix doesn't do stupid stuff with columns.
	int col_subsize = pow_3to7(subsize);

	// Allocate 23 matrices in an array
	Matrix* matrices[23];
	for (int i = 0; i < 23; i++) {
		matrices[i] = new Matrix(subsize, col_subsize);
	}

	// for each sparse matrix, multiply the appropriate submatrices
	int a_i, a_j, b_i, b_j;
	for (int i = 0; i < 23; i++) {
		get7_2d_index(u_multiply[i], a_i, a_j);
		get7_2d_index(v_multiply[i], b_i, b_j);
		// take the appropriate submatrices according to u_multiply and v_multiply
		// TODO make this part without allocating new memory. possibly by using a constructor for a submatrix that only takes a pointer to the data.
		Matrix sub_a(mat_a, a_i * subsize, a_j * col_subsize, subsize, col_subsize);
		Matrix sub_b(mat_b, b_i * subsize, b_j * col_subsize, subsize, col_subsize);

		if (i == 7 || i == 8) {
			// assuming matrices[i] is zeroed out, reverse the sign of sub_a
			Matrix::add_matrix(*matrices[i], *matrices[i], sub_a, -1, 0, 0, 0, 0, 0, 0, subsize, col_subsize);
			matmul_sparse_inner(*matrices[i], *matrices[i], sub_b);
		}
		else if (i == 0) {
			// assuming matrices[i] is zeroed out, reverse the sign of sub_b
			Matrix::add_matrix(*matrices[i], *matrices[i], sub_b, -1, 0, 0, 0, 0, 0, 0, subsize, col_subsize);
			matmul_sparse_inner(*matrices[i], sub_a, *matrices[i]);
		}
		else {
			// easy case:
			matmul_sparse_inner(*matrices[i], sub_a, sub_b);
		}
	}
	
	// now we have 23 matrices, we need to add them together to the right submatrices of result
	int res_i, res_j;
	for (int i = 0; i < 23; ++i) {
		get7_2d_index(w_add[i], res_i, res_j);
		Matrix::add_matrix(result, result, *matrices[i], 1, res_i * subsize, res_j * col_subsize, 0, 0, res_i * subsize, res_j * col_subsize, subsize, col_subsize);
	}
	return;
}

// this function multiplies 2 matrices using the fast sparse alternative basis Matrix algorithm
void matmul_sparse(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
	// make sure the matrices are square
	if (mat_a.rows() != mat_a.cols() || mat_b.rows() != mat_b.cols()) {
		std::cout << "\nError: The matrices must be square\n";
		return;
	}
	
	int logsize = log3(mat_a.rows());
	int new_size = (int)pow(7, logsize);
	// create a new matrix who's number of columns is 7 to the power of log3.
	Matrix new_a(mat_a.rows(), new_size);
	Matrix new_b(mat_a.rows(), new_size);

	// copy the matrices to the new matrices
	for (int i = 0; i < mat_a.rows(); i++) {
		for (int j = 0; j < mat_a.cols(); j++) {
			new_a(i, j) = mat_a(i, j);
			new_b(i, j) = mat_b(i, j);
		}
	}

	// TODO - make the transfers recursive and not just a single step.

	// this should be a different transfer for a and b.
	base_dim_transfer_recursive(new_a, mat_a.rows(), phi_matrix);
	base_dim_transfer_recursive(new_b, mat_b.rows(), psi_matrix);

	Matrix new_dim_result(new_a.rows(), new_a.cols());

	matmul_sparse_inner(new_dim_result, new_a, new_b);

	// TODO - make the reverse transfer recursive as well.
	base_dim_reverse_transfer_recursive(new_dim_result, mat_a.rows());

	// copy the result to the result matrix
	for (int i = 0; i < mat_a.rows(); i++) {
		for (int j = 0; j < mat_a.cols(); j++) {
			result(i, j) = new_dim_result(i, j);
		}
	}
}