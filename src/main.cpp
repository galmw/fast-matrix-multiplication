
#include <iostream>
#include <iomanip>
#include <vector>
#include "matrix.h"
#include "mult_functions.h"

using namespace std;

#define COLUMN_WIDTH 	 (13)
#define NUM_ITERATIONS	 (8)
#define PRINT_MATRICES	 (false)


// this function receives a matrix, an algorithm, and a pointer to a time variable and return the output matrix
Matrix run_algorithm(Matrix &mat_a, Matrix &mat_b, void (*algorithm)(Matrix &, Matrix &, Matrix &), double *time_taken) {
	Matrix result = Matrix(mat_a.rows(), mat_b.cols());
	clock_t start = clock();
	algorithm(result, mat_a, mat_b);
	clock_t end = clock();
	*time_taken = (double)(end - start) / CLOCKS_PER_SEC;
	return result;
}

int main() {
	
	std::cout << "Starting!" << std::endl;
	
	double time_taken;
	vector<double> standard_times, dgemm_times, strassen_times, faster_times;
	
	for (auto i = 0; i < NUM_ITERATIONS; ++i) {
		std::cout << "Testing with matrix size: " << (2 << i) << std::endl;
		
		Matrix matrix_a = Matrix::create_random(2 << i, 2 << i);
		Matrix matrix_b = Matrix::create_random(2 << i, 2 << i);
		// measure the time of the standard matrix multiplication
		
		Matrix result_dgemm = run_algorithm(matrix_a, matrix_b, dgemm, &time_taken);
		dgemm_times.push_back(time_taken);

		Matrix result_standard = run_algorithm(matrix_a, matrix_b, standard_mat_mul, &time_taken);
		standard_times.push_back(time_taken);

		Matrix result_strassen = run_algorithm(matrix_a, matrix_b, strassen, &time_taken);
		strassen_times.push_back(time_taken);
		/*
		const matrix &result_faster = run_algorithm(matrix_a, matrix_b, faster_mat_mul, &time_taken);
		faster_times.push_back(time_taken);
		*/
		faster_times.push_back(0);

		if (!Matrix::equal(result_standard, result_dgemm) || !Matrix::equal(result_standard, result_strassen)) {
			std::cout << "Something went wrong - The results are not equal" << std::endl;
		}

		if (PRINT_MATRICES) {
			std::cout << "Standard matrix:" << std::endl;
			std::cout << result_standard << std::endl;

			std::cout << "DGEMM matrix:" << std::endl;
			std::cout << result_dgemm << std::endl;

			std::cout << "Strassen matrix:" << std::endl;
			std::cout << result_strassen << std::endl;
		}
	}

	// print the results as a table
	std::cout << setw(COLUMN_WIDTH) << "Matrix size"
			  << setw(COLUMN_WIDTH) << "  DGEMM time"
			  << setw(COLUMN_WIDTH) << "  Standard time"	  
			  << setw(COLUMN_WIDTH) << "  Strassen times"
			  << setw(COLUMN_WIDTH) << "  Faster time" << std::endl;
	
	for (auto i = 0; i < NUM_ITERATIONS; ++i) {
		std::cout << setw(COLUMN_WIDTH) << (2 << i)
				  << setw(COLUMN_WIDTH) << dgemm_times[i] << setprecision(5)
				  << setw(COLUMN_WIDTH) << standard_times[i] << setprecision(5)		  
				  << setw(COLUMN_WIDTH) << strassen_times[i] << setprecision(5) 
				  << setw(COLUMN_WIDTH) << faster_times[i] << setprecision(5) << std::endl;
	}
	
	return 0;
}
