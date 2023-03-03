/*
 * matrix.h
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>


#define EPS 1e-10

class Matrix {
    public:
        Matrix(int, int);
        Matrix(const Matrix&);
        Matrix(const Matrix&, int, int, int, int);
        ~Matrix();
        void print();
        //Matrix(const Matrix&);
        //Matrix& operator=(const Matrix&);

        inline double& operator()(int x, int y) { return p[x][y]; }

        /*
        Matrix& operator+=(const Matrix&);
        Matrix& operator-=(const Matrix&);
        Matrix& operator*=(const Matrix&);
        Matrix& operator*=(double);
        Matrix& operator/=(double);
        */

        friend std::ostream& operator<<(std::ostream&, const Matrix&);
        friend std::istream& operator>>(std::istream&, Matrix&);

        static Matrix create_random(int, int);
        static bool equal(Matrix&, Matrix&, double eps=EPS);
        static double diff(Matrix&, Matrix&);
        static void add_matrix(Matrix &result, Matrix& matrix_a, Matrix &matrix_b, int multiplier = 1,
				int a_i = 0, int a_j = 0, int b_i = 0, int b_j = 0, int c_i = 0, int c_j = 0, int size = 0);

        int rows();
        int cols();

        friend void matmul_dgemm(Matrix&, Matrix&, Matrix&);
        friend void matmul_standard(Matrix&, Matrix&, Matrix&);
        friend void matmul_strassen(Matrix&, Matrix&, Matrix&);
        friend void matmul_ks(Matrix&, Matrix&, Matrix&);

    private:
        int rows_, cols_;
      
        double **p;
        double *arr;

        int row_base, col_base; // these can be used to redefine operator()
        int row_size, col_size; // these can be used to redefine rows() and cols() functions

        void allocSpace();
};

#endif