
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include "matrix.h"
#include "matmul_standard.h"
#include "matmul_strassen.h"
#include "matmul_ks.h"
#include "matmul_sparse.h"

using namespace std;

#define COLUMN_WIDTH 	 (16)
#define NUM_ITERATIONS	 (8)
#define PRINT_MATRICES	 (true)


// this function receives a matrix, an matmul_algorithm, and a pointer to a time variable and return the output matrix
Matrix run_algorithm(Matrix &mat_a, Matrix &mat_b, void (*matmul_algorithm)(Matrix &, Matrix &, Matrix &), double *time_taken) {
	Matrix result(mat_a.rows(), mat_b.cols());
	clock_t start = clock();
	matmul_algorithm(result, mat_a, mat_b);
	clock_t end = clock();
	*time_taken = (double)(end - start) / CLOCKS_PER_SEC;
	return result;
}

int main() {
	
	std::cout << "Starting!" << std::endl;
	
	double time_taken;
	vector<double> standard_times, dgemm_times, strassen_times, ks_times, sparse_times;
	vector<double> strassen_numerical_err, ks_numerical_err, sparse_numerical_error;
	
	for (auto i = 0; i < NUM_ITERATIONS; ++i) {
		std::cout << "Testing with matrix size: " << (2 << i) << std::endl;
		
		Matrix matrix_a = Matrix::create_random(2 << i, 2 << i);
		Matrix matrix_b = Matrix::create_random(2 << i, 2 << i);
		// measure the time of the standard matrix multiplication
		
		Matrix result_dgemm = run_algorithm(matrix_a, matrix_b, matmul_dgemm, &time_taken);
		dgemm_times.push_back(time_taken);

		Matrix result_standard = run_algorithm(matrix_a, matrix_b, matmul_standard, &time_taken);
		standard_times.push_back(time_taken);

		Matrix result_strassen = run_algorithm(matrix_a, matrix_b, matmul_strassen, &time_taken);
		strassen_times.push_back(time_taken);
		strassen_numerical_err.push_back(Matrix::diff(result_standard, result_strassen));
		
		Matrix result_ks = run_algorithm(matrix_a, matrix_b, matmul_ks, &time_taken);
		ks_times.push_back(time_taken);
		ks_numerical_err.push_back(Matrix::diff(result_standard, result_ks));
		
		if (!Matrix::equal(result_standard, result_dgemm) || 
			!Matrix::equal(result_standard, result_strassen) ||
			!Matrix::equal(result_standard, result_ks)) {
			std::cout << "Something went wrong - The results are not equal" << std::endl;
			if (PRINT_MATRICES) {
				std::cout << "Standard matrix:" << std::endl;
				std::cout << result_standard << std::endl;

				std::cout << "DGEMM matrix:" << std::endl;
				std::cout << result_dgemm << std::endl;

				std::cout << "Strassen matrix:" << std::endl;
				std::cout << result_strassen << std::endl;

				std::cout << "KS matrix:" << std::endl;
				std::cout << result_ks << std::endl;
			}
		}
	}

	// print the results as a table
	std::cout << setw(COLUMN_WIDTH) << "Matrix size"
			  << setw(COLUMN_WIDTH) << "  DGEMM times"
			  << setw(COLUMN_WIDTH) << "  Standard times"	  
			  << setw(COLUMN_WIDTH) << "  Strassen times"
			  << setw(COLUMN_WIDTH) << "  KS times"
			  << setw(COLUMN_WIDTH) << "  Strassen N.Err"
			  << setw(COLUMN_WIDTH) << "  KS N.Err" << std::endl;

	
	for (auto i = 0; i < NUM_ITERATIONS; ++i) {
		std::cout << setw(COLUMN_WIDTH) << (2 << i)
				  << setw(COLUMN_WIDTH) << dgemm_times[i] << setprecision(5)
				  << setw(COLUMN_WIDTH) << standard_times[i] << setprecision(5)		  
				  << setw(COLUMN_WIDTH) << strassen_times[i] << setprecision(5) 
				  << setw(COLUMN_WIDTH) << ks_times[i] << setprecision(5)
				  << setw(COLUMN_WIDTH) << strassen_numerical_err[i] << setprecision(5)
				  << setw(COLUMN_WIDTH) << ks_numerical_err[i] << setprecision(5) << std::endl;
	}


	// Part 2 - Sparse matrix multiplication

	for (auto i = 1; i < 2; ++i) {
		// set n to be 3 to the power of i
		int n = (int)pow(3, i);

		std::cout << "Testing with matrix size: " << n << std::endl;
		
		Matrix matrix_a = Matrix::create_random(n, n);
		Matrix matrix_b = Matrix::create_random(n, n);
		// measure the time of the standard matrix multiplication
		
		Matrix result_dgemm = run_algorithm(matrix_a, matrix_b, matmul_dgemm, &time_taken);

		Matrix result_sparse = run_algorithm(matrix_a, matrix_b, matmul_sparse, &time_taken);
		sparse_times.push_back(time_taken);
		sparse_numerical_error.push_back(Matrix::diff(result_dgemm, result_sparse));
		
		if (!Matrix::equal(result_dgemm, result_sparse)) {
			std::cout << "Something went wrong - The results are not equal" << std::endl;
			if (PRINT_MATRICES) {
				std::cout << "DGEMM matrix:" << std::endl;
				std::cout << result_dgemm << std::endl;

				std::cout << "Sparse matrix:" << std::endl;
				std::cout << result_sparse << std::endl;
			}
		}
	}
	// print the results as a table
	std::cout << setw(COLUMN_WIDTH) << "Matrix size"
			  << setw(COLUMN_WIDTH) << "  Sparse times"
			  << setw(COLUMN_WIDTH) << "  Sparse N.Err" << std::endl;

	
	for (auto i = 1; i < 2; ++i) {
		std::cout << setw(COLUMN_WIDTH) << ((int)pow(3, i))
				  << setw(COLUMN_WIDTH) << dgemm_times[i] << setprecision(5)
				  << setw(COLUMN_WIDTH) << sparse_numerical_error[i] << setprecision(5) << std::endl;
	}

	return 0;
}
