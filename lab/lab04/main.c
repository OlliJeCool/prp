#include <stdio.h>
#define MIN_VALUE 1
#define MAX_VALUE 100

void print_triangle(char c, int lines);
void print_line(char c, int n);
int read_input(int*);
void print_error(int ret, int n);

int main(void){
    int n;
    int ret = read_input(&n);
    if(!ret){
        print_triangle('*', n);
    }
    print_error(ret, n);
    return ret;
}

void print_triangle(char c, int lines){
    for(int i = lines; i >= 1; i--){
        print_line(c, i);
    }
}

void print_line(char c, int n){
    for(int i = 0; i < n; i++){
        putchar(c);
    }
    putchar('\n');
}

int read_input(int *n){
    if(scanf("%d", n) != 1){
        return 100;
    }
    if(*n < MIN_VALUE || *n > MAX_VALUE){
        return 101;
    }
    return 0;
}

void print_error(int ret, int n){
    switch (ret) {
        case 100:
            fprintf(stderr, "ERROR: Cannot read integer value from the standard input\n");
            break;
        case 101:
        fprintf(stderr, "ERROR: Given value %d is not within the range [%d, %d]\n", n, MIN_VALUE, MAX_VALUE);
            break;
        default:
            break;
    }
}
