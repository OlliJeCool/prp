#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>

typedef struct matrix {
    int* data;
    size_t rows;
    size_t cols;
} Matrix;

Matrix add_matrix(Matrix A, Matrix B);
Matrix sub(Matrix A, Matrix B);
Matrix mul(Matrix A, Matrix B);

#endif //MATRIX_H
