#include <iostream>
#include <iomanip>
#include "functions.h"

matrix standard_mat_mul(matrix mat_a, matrix mat_b) {
    matrix result(mat_a.size());
    for (int i = 0; i < mat_a.size(); i++) {
		result[i] = row(mat_b[0].size());
        for (int j = 0; j < mat_b.size(); j++) {
            result[i][j] = 0;
            for (int k = 0; k < mat_b[0].size(); k++) {
                result[i][j] += mat_a[i][k] * mat_b[k][j];
            }
         }
    }
	return result;
}

void print_matrix(matrix &matrix) {
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

matrix add_matrix(matrix matrix_a, matrix matrix_b, int multiplier = 1) {
	int size = matrix_a.size();
	for (auto i = 0; i < size; i++)
		for (auto j = 0; j < size; j++)
			matrix_a[i][j] = matrix_a[i][j] + (multiplier * matrix_b[i][j]);
	return matrix_a;
}

// this function receives a matrix and splits it into 4 sub-matrices: a00, a01, a10, a11
void split_matrix(matrix &mat, matrix &a00, matrix &a01, matrix &a10, matrix &a11) {
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
void split_matrix_and_base_transfer(matrix &mat, matrix &a00, matrix &a01, matrix &a10, matrix &a11) {
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
matrix fast_mat_mul(matrix matrix_a, matrix matrix_b) {
	int col_1 = matrix_a[0].size();
	int row_1 = matrix_a.size();
	int col_2 = matrix_b[0].size();
	int row_2 = matrix_b.size();

	if (col_1 != row_2) {
		std::cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return {};
	}

	row result_matrix_row(col_2, 0);
	matrix result_matrix(row_1, result_matrix_row);

	if (col_1 == 1) {
		result_matrix[0][0] = matrix_a[0][0] * matrix_b[0][0];
		return result_matrix;
	}
	int split_index = col_1 / 2;

	row row_vector(split_index, 0);

	matrix a00(split_index, row_vector);
	matrix a01(split_index, row_vector);
	matrix a10(split_index, row_vector);
	matrix a11(split_index, row_vector);
	matrix b00(split_index, row_vector);
	matrix b01(split_index, row_vector);
	matrix b10(split_index, row_vector);
	matrix b11(split_index, row_vector);

	// Splitting matrices A and B into 4 sub-matrices
	split_matrix(matrix_a, a00, a01, a10, a11);
	split_matrix(matrix_b, b00, b01, b10, b11);

	matrix p(fast_mat_mul(a00,
						  add_matrix(b01, b11, -1)));
	matrix q(fast_mat_mul(add_matrix(a00, a01),
						  b11));
	matrix r(fast_mat_mul(add_matrix(a10, a11),
						  b00));
	matrix s(fast_mat_mul(a11,
						  add_matrix(b10, b00, -1)));
	matrix t(fast_mat_mul(add_matrix(a00, a11),
						  add_matrix(b00, b11)));
	matrix u(fast_mat_mul(add_matrix(a01, a11, -1),
						  add_matrix(b10, b11)));
	matrix v(fast_mat_mul(add_matrix(a00, a10, -1),
						  add_matrix(b00, b01)));

	matrix result_matrix_00(add_matrix(add_matrix(add_matrix(t, s), u), q, -1));
	matrix result_matrix_01(add_matrix(p, q));
	matrix result_matrix_10(add_matrix(r, s));
	matrix result_matrix_11(add_matrix(add_matrix(add_matrix(t, p), r, -1), v, -1));

	// Fill the result matrix with the sub-matrices
	merge_matrix(result_matrix, result_matrix_00, result_matrix_01, result_matrix_10, result_matrix_11);
	return result_matrix;
}

// this function multiplies 2 matrices using the fast alternative basis matrix algorithm
matrix faster_mat_mul(matrix matrix_a, matrix matrix_b) {
	int col_1 = matrix_a[0].size();
	int row_1 = matrix_a.size();
	int col_2 = matrix_b[0].size();
	int row_2 = matrix_b.size();

	if (col_1 != row_2) {
		std::cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return {};
	}

	row result_matrix_row(col_2, 0);
	matrix result_matrix(row_1, result_matrix_row);

	if (col_1 == 1) {
		result_matrix[0][0] = matrix_a[0][0] * matrix_b[0][0];
		return result_matrix;
	}

	int split_index = col_1 / 2;

	row row_vector(split_index, 0);

	matrix a00(split_index, row_vector);
	matrix a01(split_index, row_vector);
	matrix a10(split_index, row_vector);
	matrix a11(split_index, row_vector);
	matrix b00(split_index, row_vector);
	matrix b01(split_index, row_vector);
	matrix b10(split_index, row_vector);
	matrix b11(split_index, row_vector);

	// Splitting matrices A and B into 4 sub-matrices with a base transfer
	split_matrix_and_base_transfer(matrix_a, a00, a01, a10, a11);
	split_matrix_and_base_transfer(matrix_b, b00, b01, b10, b11);	

	// using faster_mat_mul instead of fast.
	matrix m1(faster_mat_mul(a11, b11));
	matrix m2(faster_mat_mul(a10, b10));
	matrix m3(faster_mat_mul(a01, b01));
	matrix m4(faster_mat_mul(a00, b00));
	matrix m5(faster_mat_mul(add_matrix(a01, a10, -1), add_matrix(b11, b01, -1)));
	matrix m6(faster_mat_mul(add_matrix(a01, a00, -1), add_matrix(b01, b10, -1)));
	matrix m7(faster_mat_mul(add_matrix(a11, a01, -1), add_matrix(b01, b00, -1))); 

	matrix result_matrix_00(add_matrix(m4, m5));
	matrix result_matrix_01(add_matrix(add_matrix(add_matrix(m3, m5), m6, -1), m7));
	matrix result_matrix_10(add_matrix(m2, m7));
	matrix result_matrix_11(add_matrix(m1, m6, -1));

	// return to standard base
	merge_matrix_and_reverse_base_transfer(result_matrix, result_matrix_00, result_matrix_01, result_matrix_10, result_matrix_11);
	return result_matrix;
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
bool equal_matrix(matrix matrix_a, matrix matrix_b) {
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