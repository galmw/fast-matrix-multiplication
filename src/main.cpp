
#include <iostream>
#include <iomanip>
#include <vector>
#include "functions.h"
using namespace std;

// this function receives a matrix, an algorithm, and a pointer to a time variable and return the output matrix
matrix run_algorithm(matrix mat_a, matrix mat_b, matrix (*algorithm)(matrix, matrix), double *time) {
	time_t start, end;
	start = clock();
	matrix result = algorithm(mat_a, mat_b);
	end = clock();
	*time = double(end - start) / double(CLOCKS_PER_SEC);
	return result;
}

int main() {
	std::cout << "Starting" << std::endl;
	double time_taken;
	int num_iterations = 8;
	vector<double> standard_times;
	vector<double> faster_times;

	for (auto i = 0; i < num_iterations; ++i) {
		std::cout << "Testing with matrix size: " << (2 << i) << std::endl;
		
		matrix matrix_a = random_matrix(2 << i, 2 << i);
		matrix matrix_b = random_matrix(2 << i, 2 << i);
		// measure the time of the standard matrix multiplication
		
		matrix result_standard = run_algorithm(matrix_a, matrix_b, standard_mat_mul, &time_taken);
		standard_times.push_back(time_taken);

		matrix result_faster = run_algorithm(matrix_a, matrix_b, faster_mat_mul, &time_taken);
		faster_times.push_back(time_taken);

		if (!equal_matrix(result_standard, result_faster)) {
			std::cout << "Something went wrong - The results are not equal" << std::endl;
		}
	}

	// print the results as a table
	std::cout << "Matrix size\tStandard time\tFaster time" << std::endl;
	for (auto i = 0; i < num_iterations; ++i) {
		std::cout << (2 << i) << "\t\t" << standard_times[i] << setprecision(5) << "\t\t" << setw(20) << faster_times[i] << setprecision(5) << std::endl;
	}

	return 0;
}
