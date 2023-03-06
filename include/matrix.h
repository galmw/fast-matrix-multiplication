/*
 * matrix.h
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>


#define EPS 1e-10

class Submatrix {
    public:
        Submatrix();
        Submatrix(Submatrix&, int, int, int, int);

        void print();

        inline double& operator()(int x, int y) { return p[x][y]; }

        friend std::ostream& operator<<(std::ostream&, Submatrix&);
        friend std::istream& operator>>(std::istream&, Submatrix&);

        static void add_matrix(Submatrix &result, Submatrix& matrix_a, Submatrix &matrix_b, int multiplier = 1,
				int a_i = 0, int a_j = 0, int b_i = 0, int b_j = 0, int c_i = 0, int c_j = 0, int size = 0, int col_size = 0);

        int rows() const;
        int cols() const;

    protected:
        int rows_, cols_;
      
        double **p;
        double *arr;

        // these define where the submatrix starts in the parent matrix
        int row_base, col_base; 
};

class Matrix : public Submatrix {
    public:
        Matrix(int, int);
        Matrix(const Matrix&);
        Matrix(const Matrix&, int, int, int, int);
        ~Matrix();

        static Matrix create_random(int, int);
        static bool equal(Matrix&, Matrix&, double eps=EPS);
        static double diff(Matrix&, Matrix&);

        friend void matmul_dgemm(Matrix&, Matrix&, Matrix&);
        friend void matmul_standard(Matrix&, Matrix&, Matrix&);
        friend void matmul_strassen(Matrix&, Matrix&, Matrix&);
        friend void matmul_ks(Matrix&, Matrix&, Matrix&);

    private:
        void allocSpace();
};

#endif