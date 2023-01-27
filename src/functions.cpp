#include <iostream>
#include <iomanip>
#include "functions.h"

matrix standardMatMul(matrix mat_a, matrix mat_b) {
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

int basic[4][4] = {{1, 0, 0, 0},
                            {0, 1, -1, 1},
                            {0, 0, -1, 1},
                            {0, 1, 0, 1}};

// this function generates a random matrix of size n x n
/* void generateMatrix(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
} */

void alt_base_mat_mul(int a[2][2], int b[2][2], int result[2][2]) {
    int a11 = a[0][0];
    int a12 = a[0][1];
    int a21 = a[1][0];
    int a22 = a[1][1];
    int b11 = b[0][0];
    int b12 = b[0][1];
    int b21 = b[1][0];
    int b22 = b[1][1];
    int p1 = a11 * (b12 - b22);
    int p2 = (a11 + a12) * b22;
    int p3 = (a21 + a22) * b11;
    int p4 = a22 * (b21 - b11);
    int p5 = (a11 + a22) * (b11 + b22);
    int p6 = (a12 - a22) * (b21 + b22);
    int p7 = (a11 - a21) * (b11 + b12);
    result[0][0] = p5 + p4 - p2 + p6;
    result[0][1] = p1 + p2;
    result[1][0] = p3 + p4;
    result[1][1] = p1 + p5 - p3 - p7;
}


void print_matrix(std::string display, matrix matrix,
		int start_row, int start_column, int end_row,
		int end_column) {
	std::cout << std::endl << display << std::endl;
	for (int i = start_row; i <= end_row; i++) {
		for (int j = start_column; j <= end_column; j++) {
            std::cout << std::setw(10);
            std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return;
}

matrix add_matrix(matrix matrix_A, matrix matrix_B, int split_index, int multiplier = 1) {
	for (auto i = 0; i < split_index; i++)
		for (auto j = 0; j < split_index; j++)
			matrix_A[i][j] = matrix_A[i][j] + (multiplier * matrix_B[i][j]);
	return matrix_A;
}

matrix multiply_matrix(matrix matrix_A, matrix matrix_B) {
	int col_1 = matrix_A[0].size();
	int row_1 = matrix_A.size();
	int col_2 = matrix_B[0].size();
	int row_2 = matrix_B.size();

	if (col_1 != row_2) {
		std::cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return {};
	}

	row result_matrix_row(col_2, 0);
	matrix result_matrix(row_1,
									result_matrix_row);

	if (col_1 == 1)
		result_matrix[0][0]
			= matrix_A[0][0] * matrix_B[0][0];
	else {
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

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				a00[i][j] = matrix_A[i][j];
				a01[i][j] = matrix_A[i][j + split_index];
				a10[i][j] = matrix_A[split_index + i][j];
				a11[i][j] = matrix_A[i + split_index]
									[j + split_index];
				b00[i][j] = matrix_B[i][j];
				b01[i][j] = matrix_B[i][j + split_index];
				b10[i][j] = matrix_B[split_index + i][j];
				b11[i][j] = matrix_B[i + split_index]
									[j + split_index];
			}

		matrix p(multiply_matrix(
			a00, add_matrix(b01, b11, split_index, -1)));
		matrix q(multiply_matrix(
			add_matrix(a00, a01, split_index), b11));
		matrix r(multiply_matrix(
			add_matrix(a10, a11, split_index), b00));
		matrix s(multiply_matrix(
			a11, add_matrix(b10, b00, split_index, -1)));
		matrix t(multiply_matrix(
			add_matrix(a00, a11, split_index),
			add_matrix(b00, b11, split_index)));
		matrix u(multiply_matrix(
			add_matrix(a01, a11, split_index, -1),
			add_matrix(b10, b11, split_index)));
		matrix v(multiply_matrix(
			add_matrix(a00, a10, split_index, -1),
			add_matrix(b00, b01, split_index)));

		matrix result_matrix_00(add_matrix(
			add_matrix(add_matrix(t, s, split_index), u,
					split_index),
			q, split_index, -1));
		matrix result_matrix_01(
			add_matrix(p, q, split_index));
		matrix result_matrix_10(
			add_matrix(r, s, split_index));
		matrix result_matrix_11(add_matrix(
			add_matrix(add_matrix(t, p, split_index), r,
					split_index, -1),
			v, split_index, -1));

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				result_matrix[i][j]
					= result_matrix_00[i][j];
				result_matrix[i][j + split_index]
					= result_matrix_01[i][j];
				result_matrix[split_index + i][j]
					= result_matrix_10[i][j];
				result_matrix[i + split_index]
							[j + split_index]
					= result_matrix_11[i][j];
			}

		a00.clear();
		a01.clear();
		a10.clear();
		a11.clear();
		b00.clear();
		b01.clear();
		b10.clear();
		b11.clear();
		p.clear();
		q.clear();
		r.clear();
		s.clear();
		t.clear();
		u.clear();
		v.clear();
		result_matrix_00.clear();
		result_matrix_01.clear();
		result_matrix_10.clear();
		result_matrix_11.clear();
	}
	return result_matrix;
}



// Time Complexity: T(N) = 7T(N/2) + O(N^2) => O(N^Log7)
// which is approximately O(N^2.8074) Code Contributed By:
// lucasletum

/*
void fast_mat_mul(int [][] a, int [][] b, int [][] c) {
    base_transer(a, a_tilda);
    base_transer(b, b_tilda);
    base_transer(c, c_tilda);
    reverse_base_transer(c_tilda, c);

} */