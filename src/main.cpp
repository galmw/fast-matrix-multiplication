
#include <iostream>
#include <iomanip>
#include <vector>
#include "functions.h"
using namespace std;

int main()
{
	std::cout << "Starting" << std::endl;
	time_t start, end;
	double time_taken;
	int num_iterations = 8;
	vector<double> standard_times;
	vector<double> faster_times;

	for (auto i = 0; i < num_iterations; ++i) {
		std::cout << "Testing with matrix size: " << (2 << i) << std::endl;
		
		matrix matrix_a = random_matrix(2 << i, 2 << i);
		matrix matrix_b = random_matrix(2 << i, 2 << i);
		// measure the time of the standard matrix multiplication
		
		start = clock();
		matrix result_standard = standard_mat_mul(matrix_a, matrix_b);
		end = clock();
		time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		standard_times.push_back(time_taken);
		
		start = clock();
		matrix result_faster = faster_mat_mul(matrix_a, matrix_b);
		end = clock();
		time_taken = double(end - start) / double(CLOCKS_PER_SEC);
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
