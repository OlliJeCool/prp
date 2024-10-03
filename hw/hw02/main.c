#include <stdio.h>
#define MAX 10000
#define MIN (-10000)

int main(){
    int input;
    int total = 0, sum = 0, max = 0, min = 0, odd = 0, pos = 0;

    while(scanf("%d", &input) != 0){
        if(total != 0){ printf(", "); }
        if(input <= MAX && input >= MIN){
            total++;
            sum += input;
            max = input >= max ? input : max;
            min = input <= min ? input : total == 1 ? input : min;
            pos = input > 0 ? pos + 1 : pos;
            odd = input % 2 == 1 ? odd + 1 : odd;
        } else {
            fprintf(stderr, "Error: Vstup mimo interval!");
            return 100;
        }

        printf("Pocet cisel: %d", total);
        printf("Pocet kladnych: %d", pos);
        printf("Pocet negativnich: %d", total - pos);
        printf("Procento kladnych: %.2f", (double)pos/total * 100);
        printf("Procento negativnich: %.2f", (double)(total-pos)/total*100);


    }
    return 0;
}
