#include <errno.h>
#include <stdio.h>

int takeAndValidateInput(int*, int*, int*);
void printRoof(int);
void printBase(int, int, int);
void printLine(int, int, int, int, int);
void printFenceLine(int, int, int);
void printError(int);

int main(){
    int height = 0, width = 0, fenceHeight = 0;
    int ret = takeAndValidateInput(&width, &height, &fenceHeight);
    if(!ret) {
        printRoof(width);
        printBase(width, height, fenceHeight);
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
        case 103:
            fprintf(stderr, "Error: Neplatna velikost plotu!\n");
            break;
        default:
            break;
    }
 }

int takeAndValidateInput(int *w, int *h, int *fH){
    int result = scanf("%d %d", w, h);
    if(result != 2){
        return 100;
    }
    if(*fH >= *h){
        return 103;
    }
    if(*w > 69 || *h > 69 || *w < 3 || *h < 3){
        return 101;
    }
    if(*w % 2 != 1){
        return 102;
    }
    if(*h == *w){
        if(scanf("%d", fH) != 1){
            return 100;
        }
        if(*fH >= *h || *fH <= 0){
            return 103;
        }
    }
    return 0;
}

void printBase(int w, int h, int fH) {
    for(int i = 0; i < h; i++) {
        printLine(w, h, i, i%2, fH == 0 ? 1 : 0);
        if(fH != 0){
            printFenceLine(h, i, fH);
        }
        putchar('\n');
    }
}

void printLine(int w, int h, int currentH, int offset, int simple) {
    if(currentH == 0 || currentH == h-1) {
        for(int i = 0; i < w; i++) {
            putchar('X');
        }
    }
    else if(simple){
        printf("%*c", w-1, 'X');
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

void printFenceLine(int h, int currentHeigh, int fH){
    if(h-currentHeigh > fH){
        return;
    }
    if(currentHeigh == h-fH || currentHeigh == h-1){
        if(fH%2 == 1){
            putchar('|');
        }
        for(int i = 0; i < fH/2; i++){
            printf("-|");
        }
    }
    else{
        if(fH%2 == 1){
            putchar(' ');
        }
        for(int i = 0; i < fH/2; i++){
            printf(" |");
        }
    }
}

void printRoof(int w){
    printf("%*c\n", w/2+1, 'X');
    for(int i = 1, spaces = 1; i < w/2; i++, spaces += 2){
        printf("%*c%*c\n", w/2-i+1, 'X', spaces + 1, 'X');
    }
}
