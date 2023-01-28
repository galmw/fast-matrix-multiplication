
#include <iostream>
#include "functions.h"
using namespace std;

int main()
{
	
	matrix matrix_a = { { 1, 2},
						{ 3, 4} };
	
	matrix matrix_b = { { 1, 2},
						{ 3, 4} };
	
	matrix matrix_c = { { 1, 3, 1, 1 },
						{ 2, 4, 3, 2 },
						{ 3, 8, 4, 3 },
						{ 2, 9, 5, 2 } };

	matrix matrix_d = { { 1, 1, 6, 1 },
						{ 2, 0, 7, 2 },
						{ 3, 2, 8, 3 },
						{ 2, 2, 1, 2 } };
	
	std::cout << "Starting" << std::endl;

	matrix result_2_standard = standard_mat_mul(matrix_a, matrix_b);
	matrix result_2_fast = fast_mat_mul(matrix_a, matrix_b);
	matrix result_2_faster = faster_mat_mul(matrix_a, matrix_b);

	matrix result_4_standard = standard_mat_mul(matrix_c, matrix_d);
	matrix result_4_fast = fast_mat_mul(matrix_c, matrix_d);
	matrix result_4_faster = faster_mat_mul(matrix_c, matrix_d);
	
    std::cout << "Done" << std::endl;
	std::cout << "Standard Matrix Multiplication" << std::endl;
    print_matrix(result_2_standard);

	std::cout << "Fast Matrix Multiplication" << std::endl;
	print_matrix(result_2_fast);

	std::cout << "Faster Matrix Multiplication" << std::endl;
	print_matrix(result_2_faster);

	std::cout << "Standard Matrix Multiplication" << std::endl;
	print_matrix(result_4_standard);
	std::cout << "Fast Matrix Multiplication" << std::endl;
	print_matrix(result_4_fast);

	std::cout << "Faster Matrix Multiplication" << std::endl;
	print_matrix(result_4_faster);


	return 0;
}
