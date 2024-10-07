#include <stdio.h>

int main(void){
    int rep = 10;
    int rev = 0;
    if(rev){
    for (int i = 1; i <= rep; i++) {
        for(int j = 1; j <= i; j++){
            printf("*");
        }
        printf("\n");
    }
    }
    else{
        for (int i = rep; i >= 1; i--) {
            for(int j = 1; j <= i; j++){
                printf("*");
            }
            printf("\n");
        }
    }

    int sumMatrix[10][10];

    /*for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            int temp = 10*i;
            printf("%3d", temp+j);
        }
        printf("\n");
        }*/
    int sumMatrixSize = sizeof(sumMatrix)/sizeof(sumMatrix[0]);

    for(int i = 0; i < sumMatrixSize; i++){
        for(int j = 0; j < sumMatrixSize; j++){
            sumMatrix[i][j] = i*10 + j;
            printf("%3d", sumMatrix[i][j]);
        }
        printf("\n");
    }

    for(int n = 0; n < sumMatrixSize; n++){
        for(int m = 0; m < n; m++){
            printf("   ");
        }
        printf("%3d\n", sumMatrix[n][n]);
    }


    for(int i = 0; i < sumMatrixSize; i++){
        for(int m = 0; m < sumMatrixSize-1-i; m++){
            printf("   ");
        }
        printf("%3d\n", sumMatrix[i][sumMatrixSize-1-i]);
    }

    return 0;
}
