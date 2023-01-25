
#include <iostream>
#include "functions.h"
using namespace std;


int main()
{
    std::cout << "Hi!" << '\n';
    // int matrix_size = 2;
    int m1[2][2] = {{1, 2},
                  {3, 4}};
    
    int m2[2][2] = {{3, 4},
                    {5, 6}};
    
    int m3[2][2];
    fastMatMul(m1, m2, m3);
    
    std::cout << "Done" << std::endl;
    standardMatMul(m1, m2);
    std::cout << "Done Again" << std::endl;
}