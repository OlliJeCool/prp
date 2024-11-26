#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
Matrix create(int r, int c) {
    int* data;
    if((data = (int*)malloc(r*c*sizeof(int))) == NULL) {
        exit(1);
    }
    return (Matrix){ .rows = r, .cols = c, .data = data };
}


Matrix addm(Matrix A, Matrix B) {
    if(A.rows != B.rows || A.cols != B.cols) {
        free(A.data);
        free(B.data);
        exit(1);
    }
    int r = A.rows, c = A.cols;
    Matrix output = create(r, c);
    for(int i = 0; i < r*c; i++) {
        output.data[i] = A.data[i] + B.data[i];
    }
    return output;
}

Matrix subm(Matrix A, Matrix B) {
    if(A.rows != B.rows || A.cols != B.cols) {
        free(A.data);
        free(B.data);
        exit(1);
    }
    int r = A.rows, c = A.cols;
    Matrix output = create(r, c);
    for(int i = 0; i < r*c; i++) {
        output.data[i] = A.data[i] - B.data[i];
    }
    return output;
}

Matrix mulm(Matrix A, Matrix B) {
    if(A.cols != B.rows) {
        free(A.data);
        free(B.data);
        exit(1);
    }
    Matrix output = create(A.rows, B.cols);
    for(int i = 0; i < A.rows; i++) {
        for(int j = 0; j < B.cols; j++) {
            int temp = 0;
            for(int k = 0; k < B.rows; k++) {
                temp += A.data[i*A.cols+k] * B.data[k*B.cols+j];
            }
            output.data[i*B.cols+j] = temp;
        }
    }
    return output;
}

void printm(Matrix m) {
    printf("%d %d\n", m.rows, m.cols);
    for(int i =0; i < m.rows;  i++) {
        for(int j = 0; j < m.cols; j++) {
            printf("%3d ", m.data[i*m.cols+j]);
        }
        putchar('\n');
    }
}
