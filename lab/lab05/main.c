#include <stdio.h>

int main(){
    /*int x = 10;
    int* px = &x;

    printf("px = %lu\n", (long unsigned int)px);
    printf("px = %p\n", px);
    printf("*px = %d\n", *px);

    char c = 10;
    int x = 10;
    int* px = &x;
    char* pc = &c;

    printf("sizeof(c) = %ld\n", sizeof(c));
    printf("sizeof(x) = %ld\n", sizeof(x));
    printf("sizeof(px) = %ld\n", sizeof(px));
    printf("sizeof(pc) = %ld\n", sizeof(pc));
    printf("sizeof(char* px) = %ld\n", (long unsigned int)(char*)px);
    printf("(pc - px) = %ld\n", (pc - (char*)px));

    int x;
    char *pcx = (char**)&x;
    pcx[0] = 'a';
    pcx[1] = 'b';
    pcx[2] = 'c';
    pcx[3] = '\0';
    printf("x = %d\n", x);
    printf("&x = %ld\n", &x);
    printf("&x = %s\n", &x); */


    int array[] = {5, -6, 0, 8, -9, 3, 1, -4};
    int *up = array;
    int **uup = &up;

    printf("array[1] = %d \n", array[1]);
    printf("array[1] + 4 = %d \n", array[1] + 4);
    printf("(array + 1)[2] = %d \n", (array + 1)[2]);

    printf("*up = %d \n", *up);
    printf("*up + 4 = %d \n", *up + 4);
    printf("*(up + 1) = %d \n", *(up + 1));

    printf("**uup = %2d \n", **uup);
    printf("*(*uup + 2) = %2d \n", *(*uup + 2));
    printf("**uup + 4 = %2d \n", **uup + 4);

    return 0;
}
