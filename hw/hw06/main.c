#include <stdio.h>
#include <stdlib.h>


#define MAX_MATRICES 100
#define MAX_OPERATIONS 100
#define ERROR_STATUS 100

typedef struct matrix {
    int* data;
    size_t rows;
    size_t cols;
    char name;
} Matrix;

Matrix* create(int r, int c);
Matrix* addm(Matrix* A, Matrix* B);
Matrix* subm(Matrix* A, Matrix* B);
Matrix* mulm(Matrix* A, Matrix* B);
void freem(Matrix* M);
void freemultiple(Matrix** M, int count);
void printm(Matrix* M);
int loadInput(Matrix**, char*, int*, int*);
Matrix** evaluate(Matrix**, char*, int);

void showMatrixArray(Matrix** array) {
    for(int i = 0; i < 10;i++) {
        printf("%c", array[i] ? array[i]->name : '0');
    }
    putchar('\n');
}

int main(){
    Matrix* matricies[MAX_MATRICES] = { NULL };
    char operations[MAX_OPERATIONS];
    int ocount = 0, mcount = 0;
    int ret = loadInput(matricies, operations, &ocount, &mcount);
    if(ret != 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        freemultiple(matricies, mcount);
        return ERROR_STATUS;
    }
    /*
    Matrix* mul1 = mulm(matricies[0],matricies[1]);
    Matrix* mul2 = mulm(matricies[3], matricies[4]);
    Matrix* temp1 = subm(mul1, matricies[2]);
    Matrix* temp2 = addm(temp1, mul2);
    Matrix* res = addm(temp2, matricies[5]);
    printm(res);*/



    Matrix** result = evaluate(matricies, operations, ocount);
    if(!result) {
        showMatrixArray(result);
        showMatrixArray(matricies);
        fprintf(stderr, "Error: Chybny vstup!\n");
        freemultiple(result, mcount);
        return ERROR_STATUS;
    }
    printm(result[0]);
    freem(result[0]);

}

int loadInput(Matrix** matricies, char* operations, int* ocount, int* mcount) {
    int x,y;
    char operator;
    int names = 65;
    while(scanf("%d %d", &x, &y) == 2) {
        Matrix* mat = create(x, y);
        if(!mat) {
            return ERROR_STATUS;
        }
        mat->name = names++;

        for (int i = 0; i < x*y; i++) {
            if(scanf("%d", &mat->data[i]) != 1) {
                freem(mat);
                return ERROR_STATUS;
            }
        }
        matricies[(*mcount)++] = mat;

        if(scanf(" %c", &operator) != 1) break;
        operations[(*ocount)++] = operator;
    }
    return 0;
}

Matrix** evaluate(Matrix** matricies, char*  operators, int count) {
    for(int i = 0; i < count;  i++) {
        if(operators[i] == '*') {
            Matrix* mres = mulm(matricies[i], matricies[i+1]);
            if(!mres) {
                return NULL;
            }
            freem(matricies[i]);
            matricies[i] = mres;
            freem(matricies[i+1]);
            matricies[i+1] = NULL;
            for(int j = i+1; j < count; j++) {
                matricies[j] = matricies[j+1];
                operators[j-1] = operators[j];
            }
            count--;
            i--;
        }
    }
    for(int i = 0; i < count; i++) {
        Matrix* result;
        if(operators[i] == '-') {
            result= subm(matricies[i], matricies[i+1]);
        }
        else {
            result = addm(matricies[i], matricies[ i+1]);
        }
        if(!result) {
                return NULL;
        }
        freem(matricies[i]);
        matricies[i] = result;
        freem(matricies[i+1]);
        matricies[i+1] = NULL;
        for(int j = i+1; j < count; j++) {
            matricies[j] = matricies[j+1];
            operators[j-1] = operators[j];
        }
        count--;
        i--;
    }
    return matricies;
}

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
        if(matricies[i]){
            freem(matricies[i]);
            matricies[i] = NULL;
        }
    }
}

void printm(Matrix* M) {
    printf("%zd %zd\n", M->rows, M->cols);
    for(int i =0; i < M->rows;  i++) {
        for(int j = 0; j < M->cols; j++) {
            if(j != 0) {
                printf(" ");
            }
            printf("%d", M->data[i*M->cols+j]);
        }
        putchar('\n');
    }
}

