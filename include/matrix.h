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

        inline double& operator()(int x, int y) { return p[row_base_ + x][col_base_ + y]; }

        friend std::ostream& operator<<(std::ostream&, Submatrix&);
        friend std::istream& operator>>(std::istream&, Submatrix&);

        static void add_matrix(Submatrix &result, Submatrix& matrix_a, Submatrix &matrix_b, int multiplier = 1);
        static void copy(Submatrix &, Submatrix &, int size=0, int cols_size=0);
        static void clear(Submatrix &);

        int rows() const;
        int cols() const;

    protected:
        int rows_, cols_;
      
        double **p;
        double *arr;

        // these define where the submatrix starts in the parent matrix
        int row_base_, col_base_; 
};

class Matrix : public Submatrix {
    public:
        Matrix(int, int);
        Matrix(const Matrix&);
        Matrix(Submatrix&, int, int, int, int);
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