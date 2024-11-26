#include "matrix.h"

int main(){
    int a_data[] = { 1,2 };
    Matrix A = { .rows = 2, .cols = 2, .data = a_data };
    int b_data[] = { 1,2 };
    Matrix B = { .rows = 2, .cols = 2, .data = b_data };

    Matrix new = add_matrix(A, B);
}