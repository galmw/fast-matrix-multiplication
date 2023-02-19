#include <iostream>
#include <iomanip>
#include "matrix.h"
#include <Accelerate/Accelerate.h>


// This function takes as input two matrices and a refernce to output Matrix, and multiplies them using dgemm
void matmul_dgemm(Matrix& result, Matrix& mat_a, Matrix& mat_b)
{
    double alpha = 1.0;
    double beta = 0.0;
    int m = mat_a.rows();
    int n = mat_b.cols();
    int k = mat_a.cols();

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, mat_a.arr, k, mat_b.arr, n, beta, result.arr, n);
}

void matmul_standard(Matrix &result, Matrix &mat_a, Matrix &mat_b) {
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
