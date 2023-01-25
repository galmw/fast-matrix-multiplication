#include <iostream>
#include "functions.h"

void fastMatMul(int m1[2][2], int m2[2][2], int result[2][2]) {
    return;
}

void standardMatMul(int mat1[][C1], int mat2[][C2])
{
    int rslt[R1][C2];
 
    std::cout << "Multiplication of given two matrices is:\n";
 
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            rslt[i][j] = 0;
 
            for (int k = 0; k < R2; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
 
            std::cout << rslt[i][j] << "\t";
        }
 
        std::cout << std::endl;
    }
}
 