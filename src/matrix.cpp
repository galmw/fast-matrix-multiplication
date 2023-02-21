/*
 * matrix.cpp
 */

#include <stdexcept>
#include "matrix.h"


#define EPS 1e-10

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
}

// Matrix copy constructor
Matrix::Matrix(const Matrix& mat) {
    rows_ = mat.rows_;
    cols_ = mat.cols_;
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = mat.p[i][j];
        }
    }
}

Matrix::~Matrix()
{
    delete arr;
    delete[] p;
}

void Matrix::print() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << p[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
/* STATIC CLASS FUNCTIONS
 ********************************/

// this function returns a random matrix with the given size
Matrix Matrix::create_random(int m, int n) {
	Matrix result(m, n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
            // generate a random double uniformly distributed between -1 and 1
            result.p[i][j] = (double)rand() / (double)RAND_MAX * 2 - 1;

            // generate a random integer between -5 and 5. TODO - make this any random double between -1 and 1.
            //result.p[i][j] = rand() % 11 - 5;
		}
	}
	return result;
}

// this function receives a Matrix and splits it into 4 sub-matrices: a00, a01, a10, a11
void Matrix::split_matrix(Matrix &mat, Matrix &a00, Matrix &a01, Matrix &a10, Matrix &a11, int orig_size) {
	int size = orig_size / 2;

	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			a00.p[i][j] = mat.p[i][j];
			a01.p[i][j] = mat.p[i][j + size];
			a10.p[i][j] = mat.p[i + size][j];
			a11.p[i][j] = mat.p[i + size][j + size];
		}
	}
}

/* PRIVATE HELPER FUNCTIONS
 ********************************/

void Matrix::allocSpace()
{
    arr = new double[rows_ * cols_];
    p = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        p[i] = &arr[i * cols_];
    }
}

int Matrix::rows() {
    return rows_;
}

int Matrix::cols() {
    return cols_;
}

/* NON-MEMBER FUNCTIONS
 ********************************/

void Matrix::add_matrix(Matrix &result, Matrix& matrix_a, Matrix &matrix_b, int multiplier,
				int a_i, int a_j, int b_i, int b_j, int c_i, int c_j, int size) {
    if (size == 0) {
		size = matrix_a.rows();
	}
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			result.p[c_i + i][c_j + j] = matrix_a.p[a_i + i][a_j + j] + (multiplier * matrix_b.p[b_i + i][b_j + j]);
		}
	}
}

// this function recieves 4 sub-matrices and returns a Matrix
void Matrix::merge_matrix(Matrix &result, Matrix &a00, Matrix &a01, Matrix &a10, Matrix &a11) {
    int size = a00.rows();

    // Fill the result Matrix with the sub-matrices
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			result.p[i][j] = a00.p[i][j];
			result.p[i][j + size] = a01.p[i][j];
			result.p[size + i][j] = a10.p[i][j];
			result.p[i + size][j + size] = a11.p[i][j];
		}
	}
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m.p[i][0];
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m.p[i][j];
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            is >> m.p[i][j];
        }
    }
    return is;
}

// this function receives two matrices and returns true iff they are equal
bool Matrix::equal(Matrix &matrix_a, Matrix &matrix_b, double eps) {
	int col_1 = matrix_a.cols();
	int row_1 = matrix_a.rows();
	int col_2 = matrix_b.cols();
	int row_2 = matrix_b.rows();

	if (col_1 != col_2 || row_1 != row_2) {
		return false;
	}

	for (int i = 0; i < row_1; i++) {
		for (int j = 0; j < col_1; j++) {
            // check if the absoulte value of the difference between the two numbers is less than eps
            if (abs(matrix_a.p[i][j] - matrix_b.p[i][j]) > eps) {
                return false;
            }
		}
	}
	return true;
}

// this function recevies two matrices and returns the numberical difference between them
double Matrix::diff(Matrix &matrix_a, Matrix &matrix_b) {
    int col_1 = matrix_a.cols();
    int row_1 = matrix_a.rows();
    int col_2 = matrix_b.cols();
    int row_2 = matrix_b.rows();

    if (col_1 != col_2 || row_1 != row_2) {
        return -1;
    }

    double max_diff = 0;
    for (int i = 0; i < row_1; i++) {
        for (int j = 0; j < col_1; j++) {
            double diff = abs(matrix_a.p[i][j] - matrix_b.p[i][j]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }
    return max_diff;
}