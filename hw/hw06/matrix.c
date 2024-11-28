#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

Matrix* create(int r, int c) {
    Matrix* out;
    if((out = malloc(sizeof(Matrix))) == NULL) {
        return NULL;
    }
    int* data;
    if((data = (int*)malloc(r*c*sizeof(int))) == NULL) {
        free(out);
        return NULL;
    }
    out->cols = c, out->rows = r, out->data = data;
    return out;
}

Matrix* addm(Matrix* A, Matrix* B) {
    if(A->rows != B->rows || A->cols != B->cols) {
        return NULL;
    }
    int r = A->rows, c = A->cols;
    Matrix* output = create(r, c);
    for(int i = 0; i < r*c; i++) {
        output->data[i] = A->data[i] + B->data[i];
    }
    return output;
}

Matrix* subm(Matrix* A, Matrix* B) {
    if(A->rows != B->rows || A->cols != B->cols) {
        return NULL;
    }
    int r = A->rows, c = A->cols;
    Matrix* output = create(r, c);
    for(int i = 0; i < r*c; i++) {
        output->data[i] = A->data[i] - B->data[i];
    }
    return output;
}

Matrix* mulm(Matrix* A, Matrix* B) {
    if(A->cols != B->rows) {
        return NULL;
    }
    Matrix* output = create(A->rows, B->cols);
    for(int i = 0; i < A->rows; i++) {
        for(int j = 0; j < B->cols; j++) {
            int temp = 0;
            for(int k = 0; k < B->rows; k++) {
                temp += A->data[i*A->cols+k] * B-> data[k*B->cols+j];
            }
            output->data[i*B->cols+j] = temp;
        }
    }
    return output;
}

void freem(Matrix* M) {
    if(M) {
        free(M->data);
        free(M);
    }
}

void freemultiple(Matrix** matricies, int count) {
    for (int i = 0; i < count; i ++) {
        freem(matricies[i]);
    }
}

void printm(Matrix* M) {
    printf("%d %d\n", M->rows, M->cols);
    for(int i =0; i < M->rows;  i++) {
        for(int j = 0; j < M->cols; j++) {
            printf("%d ", M->data[i*M->cols+j]);
        }
        putchar('\n');
    }
}
