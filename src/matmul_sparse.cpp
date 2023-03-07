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
void base_dim_transfer_step(Submatrix &mat, int transfer_matrix[21][9]) {
	int size = mat.rows();
	if (size < 3) {
		std::cout << "Error!" << std::endl;
		return;
	}
	int subsize = size / 3;
	int col_subsize = pow_3to7(subsize);

	// Copy the contents of the submatrix into a new matrix, orig
	Matrix orig(size, size);
	Matrix::copy(orig, mat);
	Matrix::clear(mat);

	// do the base transfer from orig to mat.
	// important - mat's colmuns needs to be filled with the appropiate gaps to allow further recursive calls.
	int orig_i, orig_j, target_i, target_j;

	for (int target_index = 0; target_index < 21; target_index++) {	
		get7_2d_index(target_index, target_i, target_j);

		// for each entry in the target matrix, add the appropriate subsize*subsize submatrices from the original matrix
		Submatrix target_submat(mat, target_i * subsize, target_j * col_subsize, subsize, subsize);

		for (int orig_index = 0; orig_index < 9; ++orig_index) {		
			if (transfer_matrix[target_index][orig_index] != 0) {
				get3_2d_index(orig_index, orig_i, orig_j);
				Submatrix orig_submat(orig, orig_i * subsize, orig_j * subsize, subsize, subsize);

				Matrix::add_matrix(target_submat, target_submat, orig_submat, transfer_matrix[target_index][orig_index]);
			}
		}
	}
}

// this function receives a Submatrix in the transfered basis, 3^n * 7^n is allocated.
// It performs one step of the base transfer, and transfers it into a matrix in the original dimension.
// The minimum expected 'size' is 3.
void base_dim_reverse_transfer_step(Submatrix &mat) {
	int size = mat.rows();
	int colsize = mat.cols();
	if (size < 3) {
		std::cout << "Error!" << std::endl;
		return;
	}
	int subsize = size / 3;
	int col_subsize = colsize / 7;

	// orig contains the originial dimension of the content.
	Matrix orig(size, colsize);
	// copy the contents of mat into orig
	Submatrix::copy(orig, mat);
	// clear out the content of the destined part of mat
	Submatrix::clear(mat);

	// do the base transfer from orig to mat
	int orig_i, orig_j, target_i, target_j;

	for (int target_index = 0; target_index < 9; target_index++) {	
		get3_2d_index(target_index, target_i, target_j);

		Submatrix target_submat(mat, target_i * subsize, target_j * subsize, subsize, subsize);

		// for each entry in the target matrix, add the appropriate subsize*subsize (already reverse transfered to square) submatrices from the original matrix
		for (int orig_index = 0; orig_index < 21; orig_index++) {		
			if (tau_matrix[orig_index][target_index] != 0) {
				get7_2d_index(orig_index, orig_i, orig_j);
				Submatrix orig_submat(orig, orig_i * subsize, orig_j * col_subsize, subsize, subsize);
				Matrix::add_matrix(target_submat, target_submat, orig_submat, tau_matrix[orig_index][target_index]);
			}
		}
	}
}

// this function receives a Matrix in the standard basis, 3^n * 3^n is allocated, the full size is 3^n * 7^n,
// and transfers it recusively into a matrix in the new dimension.
void base_dim_transfer_recursive(Submatrix &mat, int transfer_matrix[21][9]) {
	int size = mat.rows();
	if (size < 3) { 
		return;
	}

	base_dim_transfer_step(mat, transfer_matrix);
	if (size > 3) {
		int subsize = size / 3;
		int col_subsize = pow_3to7(subsize);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				Submatrix submat(mat, i * subsize, j * col_subsize, subsize, col_subsize);
				base_dim_transfer_recursive(submat, transfer_matrix);
			}
		}
	}
}

void base_dim_reverse_transfer_recursive(Submatrix &mat) {
	int size = mat.rows();
	if (size < 3) { 
		return;
	}

	if (size > 3) {
		int subsize = size / 3;
		int col_subsize = pow_3to7(subsize);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				Submatrix submat(mat, i * subsize, j * col_subsize, subsize, col_subsize);
				base_dim_reverse_transfer_recursive(submat);
			}
		}
	}
	base_dim_reverse_transfer_step(mat);
}

void matmul_sparse_inner(Submatrix &result, Submatrix &mat_a, Submatrix &mat_b) {
	int size = mat_a.rows();

	if (size == 1) {
		result(0, 0) = mat_a(0, 0) * mat_b(0, 0);
		return;
	}

	int subsize = size / 3;
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
		Submatrix sub_a(mat_a, a_i * subsize, a_j * col_subsize, subsize, col_subsize);
		Submatrix sub_b(mat_b, b_i * subsize, b_j * col_subsize, subsize, col_subsize);

		if (i == 7 || i == 8) {
			// assuming matrices[i] is zeroed out, reverse the sign of sub_a
			Matrix::add_matrix(*matrices[i], *matrices[i], sub_a, -1);
			matmul_sparse_inner(*matrices[i], *matrices[i], sub_b);
		}
		else if (i == 0) {
			// assuming matrices[i] is zeroed out, reverse the sign of sub_b
			Matrix::add_matrix(*matrices[i], *matrices[i], sub_b, -1);
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

	Matrix::clear(new_a);
	Matrix::clear(new_b);
	
	// copy the matrices to the new matrices
	Matrix::copy(new_a, mat_a, mat_a.rows(), mat_a.cols());
	Matrix::copy(new_b, mat_b, mat_b.rows(), mat_b.cols());

	// this should be a different transfer for a and b.
	base_dim_transfer_recursive(new_a, phi_matrix);
	base_dim_transfer_recursive(new_b, psi_matrix);

	Matrix new_dim_result(new_a.rows(), new_a.cols());

	matmul_sparse_inner(new_dim_result, new_a, new_b);

	base_dim_reverse_transfer_recursive(new_dim_result);

	Matrix::copy(result, new_dim_result);
}