#include <stdio.h>

#include "matrix.h"

int main(){
    int a_data[] = { 76, 98, -31, 30, 30, 32 };
    Matrix A = { .rows = 2, .cols = 3, .data = a_data };
    int b_data[] = { 89, 25, 38, 1, -32, -38 };
    Matrix B = { .rows = 2, .cols = 3, .data = b_data };
    int c_data[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1};
    Matrix C = { .rows = 3, .cols = 3, .data = c_data };

    Matrix mul = subm(A,B);
    printm(mul);
}

