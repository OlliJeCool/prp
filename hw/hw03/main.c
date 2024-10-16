#include <errno.h>
#include <stdio.h>

int takeAndValidateInput(int*, int*);
void printRoof(int);
void printBase(int, int);
void printLine(int, int, int, int);
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
    for(int i = 0; i < h; i++) {
        printLine(w, h, i, i%2);
        putchar('\n');
    }
}

void printLine(int w, int h, int currentH, int offset) {
    if(currentH == 0 || currentH == h-1) {
        for(int i = 0; i < w; i++) {
            putchar('X');
        }
    }
    else {
        char options[] = {'X','o','*'};
        for(int i = 0 + offset; i < w + offset; i++) {
            if(i == 0 + offset || i == w + offset - 1) {
                putchar(options[0]);
                continue;
            }
            putchar(options[i%2+1]);
        }
    }
}

void printRoof(int w){
    printf("%*c\n", w/2+1, 'X');
    for(int i = 1, spaces = 1; i < w/2; i++, spaces += 2){
        printf("%*c%*c\n", w/2-i+1, 'X', spaces + 1, 'X');
    }
}
