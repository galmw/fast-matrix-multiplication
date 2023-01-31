#include <iostream>
#include <iomanip>
#include "functions.h"

matrix create_matrix(int size) {
	matrix mat(size, row(size));
	return mat;
}

void standard_mat_mul(matrix &result, matrix &mat_a, matrix &mat_b) {
    for (int i = 0; i < mat_a.size(); i++) {
        for (int j = 0; j < mat_b.size(); j++) {
            result[i][j] = 0;
            for (int k = 0; k < mat_b[0].size(); k++) {
                result[i][j] += mat_a[i][k] * mat_b[k][j];
            }
         }
    }
	return;
}

void print_matrix(const matrix &matrix) {
	for (auto i = 0; i < matrix.size(); i++) {
		for (auto j = 0; j < matrix[0].size(); j++) {
            std::cout << std::setw(10);
            std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return;
}

void add_matrix(matrix &result, const matrix& matrix_a, const matrix &matrix_b, int multiplier = 1, int a_i = 0, int a_j = 0, int b_i = 0, int b_j = 0, int size = 0) {
	if (size == 0) {
		size = matrix_a.size();
	}

	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			result[i][j] = matrix_a[a_i + i][a_j + j] + (multiplier * matrix_b[b_i + i][b_j + j]);
		}
	}
}

// this function receives a matrix and splits it into 4 sub-matrices: a00, a01, a10, a11
void split_matrix(const matrix &mat, matrix &a00, matrix &a01, matrix &a10, matrix &a11) {
	int size = mat[0].size() / 2;

	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			a00[i][j] = mat[i][j];
			a01[i][j] = mat[i][j + size];
			a10[i][j] = mat[i + size][j];
			a11[i][j] = mat[i + size][j + size];
		}
	}
}

// this function recieves a matrix and returns 4 sub-matrices, after a base transfer
// this can be done on one big matrix, in-place. TODO
void split_matrix_and_base_transfer(const matrix &mat, matrix &a00, matrix &a01, matrix &a10, matrix &a11) {
	int size = mat.size() / 2;

	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			a00[i][j] = mat[i][j];
			a01[i][j] = mat[i][j + size] - mat[i + size][j] + mat[i + size][j + size];
			a10[i][j] = mat[i + size][j + size] - mat[i + size][j];
			a11[i][j] = mat[i][j + size] + mat[i + size][j + size];
		}
	}
}

// this function transfers a matrix to the alternative base, in-place
void base_transfer(matrix &mat) {
	int size = mat.size() / 2;
	// step 1
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			mat[i + size][j] = mat[i + size][j + size] - mat[i + size][j];
		}
	}
	// step 2
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			mat[i + size][j + size] += mat[i][j + size];
		}
	}
	// step 3
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			mat[i][j + size] -= mat[i + size][j];
		}
	}
}

// this function reverse transfers a matrix from the alternative base, in-place
void reverse_base_transfer(matrix &mat) {
	int size = mat.size() / 2;
	// step 1
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			mat[i][j + size] += mat[i + size][j];
		}
	}
	// step 2
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			mat[i + size][j + size] -= mat[i][j + size];
		}
	}
	// step 3
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			mat[i + size][j] = mat[i + size][j + size] + mat[i + size][j];
		}
	}
}


// this function recieves 4 sub-matrices and returns a matrix after a reverse base transfer
void merge_matrix_and_reverse_base_transfer(matrix &result,
		const matrix &a00, const matrix &a01, const matrix &a10, const matrix &a11) {
	int size = a00.size();

	// Fill the result matrix with the sub-matrices with a base transfer
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			result[i][j] = a00[i][j];
			result[i][j + size] = a01[i][j] - a10[i][j];
			result[size + i][j] = a11[i][j] - a01[i][j];
			result[i + size][j + size] = a10[i][j] - a01[i][j] + a11[i][j];
		}
	}
}

// this function recieves 4 sub-matrices and returns a matrix
void merge_matrix(matrix &result, const matrix &a00, const matrix &a01, const matrix &a10, const matrix &a11) {
	int size = a00.size();

	// Fill the result matrix with the sub-matrices
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			result[i][j] = a00[i][j];
			result[i][j + size] = a01[i][j];
			result[size + i][j] = a10[i][j];
			result[i + size][j + size] = a11[i][j];
		}
	}
}

// this function multiplies 2 matrices using the Strassen algorithm
void fast_mat_mul(matrix &result, matrix &matrix_a, matrix &matrix_b) {
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
	matrix a00 = create_matrix(split_index);
	matrix a01 = create_matrix(split_index);
	matrix a10 = create_matrix(split_index);
	matrix a11 = create_matrix(split_index);
	matrix b00 = create_matrix(split_index);
	matrix b01 = create_matrix(split_index);
	matrix b10 = create_matrix(split_index);
	matrix b11 = create_matrix(split_index);

	// Splitting matrices A and B into 4 sub-matrices
	split_matrix(matrix_a, a00, a01, a10, a11);
	split_matrix(matrix_b, b00, b01, b10, b11);

	// Allocate sub-matrices
	matrix p = create_matrix(split_index);
	matrix q = create_matrix(split_index);
	matrix r = create_matrix(split_index);
	matrix s = create_matrix(split_index);
	matrix t = create_matrix(split_index);
	matrix u = create_matrix(split_index);
	matrix v = create_matrix(split_index);

	matrix temp0 = create_matrix(split_index);

	add_matrix(temp0, b01, b11, -1);
	fast_mat_mul(p, a00, temp0);

	add_matrix(temp0, a00, a01);
	fast_mat_mul(q, temp0, b11);

	add_matrix(temp0, a10, a11);
	fast_mat_mul(r, temp0, b00);
	
	add_matrix(temp0, b10, b00, -1);
	fast_mat_mul(s, a11, temp0);
	
	matrix temp1 = create_matrix(split_index);
	add_matrix(temp0, a00, a11);
	add_matrix(temp1, b00, b11);
	fast_mat_mul(t, temp0, temp1);
	
	add_matrix(temp0, a01, a11, -1);
	add_matrix(temp1, b10, b11);
	fast_mat_mul(u, temp0, temp1);

	add_matrix(temp0, a00, a10, -1);
	add_matrix(temp1, b00, b01);
	fast_mat_mul(v, temp0, temp1);
	
	// Allocate sub-matrices
	matrix result_matrix_00 = create_matrix(split_index);
	matrix result_matrix_01 = create_matrix(split_index);
	matrix result_matrix_10 = create_matrix(split_index);
	matrix result_matrix_11 = create_matrix(split_index);

	// Calculate the sub-matrices
	add_matrix(result_matrix_00, t, s);
	add_matrix(result_matrix_00, result_matrix_00, u);
	add_matrix(result_matrix_00, result_matrix_00, q, -1);

	add_matrix(result_matrix_01, p, q);
	add_matrix(result_matrix_10, r, s);

	add_matrix(result_matrix_11, t, p);
	add_matrix(result_matrix_11, result_matrix_11, r, -1);
	add_matrix(result_matrix_11, result_matrix_11, v, -1);

	// Fill the result matrix with the sub-matrices
	merge_matrix(result, result_matrix_00, result_matrix_01, result_matrix_10, result_matrix_11);
	return;
}


// this function multiplies 2 matrices using the fast alternative basis matrix algorithm
void faster_mat_mul(matrix &result, matrix &matrix_a, matrix &matrix_b) {
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
	matrix a00 = create_matrix(split_index);
	matrix a01 = create_matrix(split_index);
	matrix a10 = create_matrix(split_index);
	matrix a11 = create_matrix(split_index);
	matrix b00 = create_matrix(split_index);
	matrix b01 = create_matrix(split_index);
	matrix b10 = create_matrix(split_index);
	matrix b11 = create_matrix(split_index);

	//base_transfer(matrix_a);
	//base_transfer(matrix_b);

	// Splitting matrices A and B into 4 sub-matrices with a base transfer
	split_matrix_and_base_transfer(matrix_a, a00, a01, a10, a11);
	split_matrix_and_base_transfer(matrix_b, b00, b01, b10, b11);	

	// Allocate sub-matrices
	matrix m1 = create_matrix(split_index);
	matrix m2 = create_matrix(split_index);
	matrix m3 = create_matrix(split_index);
	matrix m4 = create_matrix(split_index);
	matrix m5 = create_matrix(split_index);
	matrix m6 = create_matrix(split_index);
	matrix m7 = create_matrix(split_index);

	// using faster_mat_mul instead of fast.
	faster_mat_mul(m1, a11, b11);
	faster_mat_mul(m2, a10, b10);
	faster_mat_mul(m3, a01, b01);
	faster_mat_mul(m4, a00, b00);

	matrix temp0 = create_matrix(split_index);
	matrix temp1 = create_matrix(split_index);
	add_matrix(temp0, a01, a10, -1);
	add_matrix(temp1, b11, b01, -1);
	faster_mat_mul(m5, temp0, temp1);

	add_matrix(temp0, a01, a00, -1);
	add_matrix(temp1, b01, b10, -1);
	faster_mat_mul(m6, temp0, temp1);

	add_matrix(temp0, a11, a01, -1);
	add_matrix(temp1, b01, b00, -1);
	faster_mat_mul(m7, temp0, temp1);
	
	// Allocate sub-matrices (this can be avoided)
	matrix result_matrix_00 = create_matrix(split_index);
	matrix result_matrix_01 = create_matrix(split_index);
	matrix result_matrix_10 = create_matrix(split_index);
	matrix result_matrix_11 = create_matrix(split_index);

	add_matrix(result_matrix_00, m4, m5);

	add_matrix(result_matrix_01, m3, m5);
	add_matrix(result_matrix_01, result_matrix_01, m6, -1);
	add_matrix(result_matrix_01, result_matrix_01, m7);

	add_matrix(result_matrix_10, m2, m7);

	add_matrix(result_matrix_11, m1, m6, -1);

	// return to standard base
	merge_matrix_and_reverse_base_transfer(result, result_matrix_00, result_matrix_01, result_matrix_10, result_matrix_11);
	return;
}


// this function returns a random matrix with the given size
matrix random_matrix(int m, int n) {
	matrix result(m, row(n, 0));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			result[i][j] = arc4random() % 10;
		}
	}
	return result;
}

// this function receives two matrices and returns true iff they are equal
bool equal_matrix(const matrix &matrix_a, const matrix &matrix_b) {
	int col_1 = matrix_a[0].size();
	int row_1 = matrix_a.size();
	int col_2 = matrix_b[0].size();
	int row_2 = matrix_b.size();

	if (col_1 != col_2 || row_1 != row_2) {
		return false;
	}

	for (int i = 0; i < row_1; i++) {
		for (int j = 0; j < col_1; j++) {
			if (matrix_a[i][j] != matrix_b[i][j]) {
				return false;
			}
		}
	}
	return true;
}
