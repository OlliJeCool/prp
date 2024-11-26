#include "matrix.h"

#include <stdlib.h>

Matrix add_matrix(Matrix A, Matrix B) {
    if(A.rows != B.rows || A.cols != B.cols) {
        exit(1);
    }
    int r = A.rows, c = A.cols;
    int* outdata;
    if((outdata = (int*)malloc(r*c*sizeof(int))) == NULL) {
        exit(1);
    }
    Matrix output = { .rows = r, .cols = c, .data = outdata };
    int i = 0, j = 0; //rows, cols
    for(int ro,co = 0; co < c, ro < r; co = co % c-1 == 0 ? 0 : co+1) {
        int index = r*i+j;
        output.data[index] = A.data[index] + B.data[index];
    }
    return output;
}
