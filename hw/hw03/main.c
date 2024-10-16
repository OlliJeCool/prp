#include <errno.h>
#include <stdio.h>

int takeAndValidateInput(int*, int*);
void printRoof(int);
void printBase(int, int);
void printLine(int, int, int);
void printError(int);

int main(){
    int height = 0, width = 0;
    int ret = takeAndValidateInput(&width, &height);
    if(!ret) {
        printRoof(width);
        printBase(width, height);
    }
    printError(ret);
    return ret;
}

void printError(int ret){
    switch(ret){
        case 100:
            fprintf(stderr, "Error: Chybny vstup!\n");
            break;
        case 101:
            fprintf(stderr, "Error: Vstup mimo interval!\n");
            break;
        case 102:
            fprintf(stderr, "Error: Sirka neni liche cislo!\n");
            break;
        default:
            break;
    }
 }

int takeAndValidateInput(int *w, int *h){
    if(scanf("%d %d", w, h) != 2){
      return 100;
    }
    if(*w > 69 || *h > 69 || *w < 3 || *h < 3){
        return 101;
    }
    if(*w % 2 != 1){
        return 102;
    }
    return 0;
}

void printBase(int w, int h) {
    printLine(w, 1, 0);
    for(int i = 0; i < h-2; i++) {
        printLine(w, 0, i%2);
    }
    printLine(w, 1, 0);
}

void printLine(int w, int simple, int offset) {
    char options[] = {'o', '*'};
    putchar('X');
    if(simple) {
        for(int i = 0; i < w-2; i++) {
            putchar('X');
        }
        putchar('X');
        putchar('\n');
    }
    else {
        for(int i = offset; i < w-2+offset; i++) {
            putchar(options[i%2]);
        }
        putchar('X');
        putchar('\n');
    }
}

void printRoof(int w){
    printf("%*c\n", w/2+1, 'X');
    for(int i = 1, spaces = 1; i < w/2; i++, spaces+=2){
        printf("%*c%*c\n", w/2-i+1, 'X', spaces + 1, 'X');
    }
}
