#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>

typedef struct matrix {
    int* data;
    size_t rows;
    size_t cols;
} Matrix;

Matrix* create(int r, int c);
Matrix* addm(Matrix* A, Matrix* B);
Matrix* subm(Matrix* A, Matrix* B);
Matrix* mulm(Matrix* A, Matrix* B);
void freem(Matrix* M);
void freemultiple(Matrix** M, int count);
void printm(Matrix* M);

#endif //MATRIX_H
