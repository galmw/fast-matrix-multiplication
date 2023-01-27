
#include <iostream>
#include "functions.h"
using namespace std;

int main()
{
	
	matrix matrix_a = { { 1, 2},
						{ 3, 4} };
	
	matrix matrix_b = { { 1, 2},
						{ 3, 4} };
	
	matrix matrix_c = { { 1, 1, 1, 1 },
						{ 2, 2, 2, 2 },
						{ 3, 3, 3, 3 },
						{ 2, 2, 2, 2 } };

	matrix matrix_d = { { 1, 1, 1, 1 },
						{ 2, 2, 2, 2 },
						{ 3, 3, 3, 3 },
						{ 2, 2, 2, 2 } };
	
	std::cout << "Starting" << std::endl;

	matrix result = standard_mat_mul(matrix_a, matrix_b);
	matrix result_2 = fast_mat_mul(matrix_a, matrix_b);

	matrix result_3 = standard_mat_mul(matrix_c, matrix_d);
	matrix result_4 = fast_mat_mul(matrix_c, matrix_d);
	
    std::cout << "Done" << std::endl;
	std::cout << "Standard Matrix Multiplication" << std::endl;
    print_matrix(result);

	std::cout << "Fast Matrix Multiplication" << std::endl;
	print_matrix(result_2);

	std::cout << "Standard Matrix Multiplication" << std::endl;
	print_matrix(result_3);
	std::cout << "Fast Matrix Multiplication" << std::endl;
	print_matrix(result_4);

	return 0;
}
