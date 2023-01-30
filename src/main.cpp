
#include <iostream>
#include <iomanip>
#include <vector>
#include "functions.h"

using namespace std;

#define COLUMN_WIDTH 	 (11)
#define NUM_ITERATIONS	 (8)

// this function receives a matrix, an algorithm, and a pointer to a time variable and return the output matrix
matrix run_algorithm(const matrix &mat_a, const matrix &mat_b, matrix (*algorithm)(const matrix &, const matrix &), double *time_taken) {
	clock_t start = clock();
	const matrix &result = algorithm(mat_a, mat_b);
	clock_t end = clock();
	*time_taken = (double)(end - start) / CLOCKS_PER_SEC;
	return result;
}


int main() {
	std::cout << "Starting" << std::endl;
	double time_taken;
	vector<double> standard_times, strassen_times, faster_times;

	for (auto i = 0; i < NUM_ITERATIONS; ++i) {
		std::cout << "Testing with matrix size: " << (2 << i) << std::endl;
		
		matrix matrix_a = random_matrix(2 << i, 2 << i);
		matrix matrix_b = random_matrix(2 << i, 2 << i);
		// measure the time of the standard matrix multiplication
		
		const matrix &result_standard = run_algorithm(matrix_a, matrix_b, standard_mat_mul, &time_taken);
		standard_times.push_back(time_taken);

		const matrix &result_strassen = run_algorithm(matrix_a, matrix_b, fast_mat_mul, &time_taken);
		strassen_times.push_back(time_taken);

		const matrix &result_faster = run_algorithm(matrix_a, matrix_b, faster_mat_mul, &time_taken);
		faster_times.push_back(time_taken);

		if (!equal_matrix(result_standard, result_strassen) || !equal_matrix(result_standard, result_faster)) {
			std::cout << "Something went wrong - The results are not equal" << std::endl;
		}
	}

	// print the results as a table
	std::cout << setw(COLUMN_WIDTH) << "Matrix size"
			  << setw(COLUMN_WIDTH) << "Standard time"
			  << setw(COLUMN_WIDTH) << "Strassen times"
			  << setw(COLUMN_WIDTH) << "Faster time" << std::endl;
	
	for (auto i = 0; i < NUM_ITERATIONS; ++i) {
		std::cout << setw(COLUMN_WIDTH) << (2 << i)
				  << setw(COLUMN_WIDTH) << standard_times[i] << setprecision(5)
				  << setw(COLUMN_WIDTH) << strassen_times[i] << setprecision(5) 
				  << setw(COLUMN_WIDTH) << faster_times[i] << setprecision(5) << std::endl;
	}

	return 0;
}
