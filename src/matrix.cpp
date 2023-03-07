/*
 * matrix.cpp
 */

#include <stdexcept>
#include "matrix.h"

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

Submatrix::Submatrix() {
    rows_ = 0;
    cols_ = 0;
    p = NULL;
    arr = NULL;
    row_base_ = 0;
    col_base_ = 0;
}

Submatrix::Submatrix(Submatrix& mat, int row_base, int col_base, int rows, int cols) {
    p = mat.p;
    row_base_ = mat.row_base_ + row_base;
    col_base_ = mat.col_base_ + col_base;
    rows_ = rows;
    cols_ = cols;
    /*
    p = mat.p + start_i;
    for (int i = 0; i < rows_; ++i) {
        p[i] += start_j;
    }
    */
}

Matrix::Matrix(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    row_base_ = 0;
    col_base_ = 0;
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

// Allocate a new matrix from a submatrix of the given matrix, starting at (i,j) and with the given size
Matrix::Matrix(Submatrix& mat, int start_i, int start_j, int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    row_base_ = 0;
    col_base_ = 0;
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = mat(start_i + i, start_j + j);
        }
    }
}

Matrix::~Matrix() {
    delete[] arr;
    delete[] p;
}

void Submatrix::print() {
    std::cout << "Matrix of size " << rows_ << "x" << cols_ << ":" << std::endl;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << (*this)(i, j) << " ";
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
            //result.p[i][j] = (double)rand() / (double)RAND_MAX * 2 - 1;

            // generate a random integer between -1 and 1. TODO - make this any random double between -1 and 1.
           result.p[i][j] = rand() % 3 - 1;
		}
	}
	return result;
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

int Submatrix::rows() const {
    return rows_;
}

int Submatrix::cols() const {
    return cols_;
}

/* NON-MEMBER FUNCTIONS
 ********************************/

// void Submatrix::add_matrix(Submatrix &result, Submatrix& matrix_a, Submatrix &matrix_b, int multiplier) {
//     int size = matrix_a.rows();
//     int col_size = matrix_a.cols();

// 	for (auto i = 0; i < size; i++) {
// 		for (auto j = 0; j < col_size; j++) {
// 			result(i, j) = matrix_a(i, j) + (multiplier * matrix_b(i, j));
// 		}
// 	}
// }


void Submatrix::add_matrix(Submatrix &result, Submatrix& matrix_a, Submatrix &matrix_b, int multiplier,
				int a_i, int a_j, int b_i, int b_j, int c_i, int c_j, int size, int col_size) {
    if (size == 0) {
		size = matrix_a.rows();
	}
    if (col_size == 0 ) {
        col_size = size;
    }
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < col_size; j++) {
			result(c_i + i, c_j + j) = matrix_a(a_i + i, a_j + j) + (multiplier * matrix_b(b_i + i, b_j + j));
		}
	}
}

ostream& operator<<(ostream& os, Submatrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m(i, 0);
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m(i, j);
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Submatrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            is >> m(i, j);
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