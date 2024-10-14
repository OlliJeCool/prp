#include <errno.h>
#include <stdio.h>
#include <utility>
int ret = 0;

void takeAndValidateInput(int*, int*);
void printRoof(int);
void printHouse(int, int);

int main(){
    int height = 0, width = 0;
    takeAndValidateInput(&height, &width);
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
    }
    if(ret != 0){ return ret; }

    return 0;
}

void takeAndValidateInput(int *w, int *h){
    if(scanf("%d %d", w, h) != 2){
        ret =  100;
        return;
    }

    if(*w > 69 || *h > 69 || *w < 3 || *h < 3){
        ret = 101;
        return;
    }

    if(*w % 2 != 1){
        ret = 102;
        return;
    }
}

void printRoof(int w){
    for(int i = 0; i < w/2; i++){

    }

}
