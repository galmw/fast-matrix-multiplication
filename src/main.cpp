
#include <iostream>
#include "functions.h"
using namespace std;

#define ROW_1 4
#define COL_1 4

#define ROW_2 4
#define COL_2 4

int main()
{
    std::cout << "Hi!" << '\n';

	matrix matrix_A = { { 1, 1, 1, 1 },
									{ 2, 2, 2, 2 },
									{ 3, 3, 3, 3 },
									{ 2, 2, 2, 2 } };

	print_matrix("Array A", matrix_A, 0, 0, ROW_1 - 1, COL_1 - 1);

	matrix matrix_B = { { 1, 1, 1, 1 },
									{ 2, 2, 2, 2 },
									{ 3, 3, 3, 3 },
									{ 2, 2, 2, 2 } };

	print_matrix("Array B", matrix_B, 0, 0, ROW_2 - 1, COL_2 - 1);

    // fastMatMul(m1, m2, m3);
    
	matrix result = standardMatMul(matrix_A, matrix_B);
    std::cout << "Done" << std::endl;
    print_matrix("Array C", result, 0, 0, ROW_1 - 1, COL_2 - 1);
	return 0;
}

/*



using namespace std;



int main()
{
	matrix matrix_A = { { 1, 1, 1, 1 },
									{ 2, 2, 2, 2 },
									{ 3, 3, 3, 3 },
									{ 2, 2, 2, 2 } };

	print("Array A", matrix_A, 0, 0, ROW_1 - 1, COL_1 - 1);

	matrix matrix_B = { { 1, 1, 1, 1 },
									{ 2, 2, 2, 2 },
									{ 3, 3, 3, 3 },
									{ 2, 2, 2, 2 } };

	print("Array B", matrix_B, 0, 0, ROW_2 - 1, COL_2 - 1);

	matrix result_matrix(
		multiply_matrix(matrix_A, matrix_B));

	print("Result Array", result_matrix, 0, 0, ROW_1 - 1,
		COL_2 - 1);
}

*/