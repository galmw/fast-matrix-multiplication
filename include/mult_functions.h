// header guard
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include "matrix.h"


void dgemm(Matrix&, Matrix&, Matrix&);

void standard_mat_mul(Matrix&, Matrix&, Matrix&);

void strassen(Matrix&, Matrix&, Matrix&);

// end of header guard
#endif