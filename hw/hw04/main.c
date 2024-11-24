#include <stdio.h>
#define MAX 1000002

int takeAndValidateInput(long long int *, int *);
void printError(int);
void evaluateNums(_Bool*, int *);
void printOutput(int*, int, long long int);
void extractPrimes(int*, _Bool*, int);

int main() {
    long long int input = 0;
    int ret = 0, primes_count = 0;
    _Bool primes[MAX+1];
    evaluateNums(primes, &primes_count);
    int primeOnly[primes_count];
    extractPrimes(primeOnly, primes, primes_count);
    while(takeAndValidateInput(&input, &ret) == 1) {
        if(!ret && input != 0) {
            printOutput(primeOnly, primes_count, input);
            continue;
        }
        break;
    }
    printError(ret);
    return ret;
}

void printOutput(int* primes, int count, long long int num) {
    _Bool first = 1;
    int power = 0;
    long long int temp = num;
    printf("Prvociselny rozklad cisla %lld je:\n", num);
    for(int i = 2; i <= count; i++) {
        int prime = *(primes+i);
        if(num == 1){
            printf("1");
            break;
        }
        if(prime > temp) {
            break;
        }

        if(temp % prime == 0) {
            temp /= prime;
            power++;
            if(temp % prime == 0){
                i--;
                continue;
            }
            printf(first ? "" : " x ");
            if(power > 1){
                printf("%d^%d", prime, power);
                first = first ? 0 : first;
                power = 0;
                continue;
            }
            printf("%d", prime);
            first = first ? 0 : first;
            power = 0;
        }
    }
    putchar('\n');
}

void printError(int ret) {
    if(ret == 100) {
        fprintf(stderr, "Error: Chybny vstup!\n");
    }
}

int takeAndValidateInput(long long int* input, int* ret) {
    int result = scanf("%lld", input);
    if(*input < 0 || result == 0) {
        *ret = 100;
    }
    return result;
}

void extractPrimes(int* primeOnly, _Bool* primes, int count) {
    int index = 2;
    for(int h = 2; h < MAX && index <= count; h++) {
        if(*(primes+h)) {
            *(primeOnly+index) = h;
            index++;
        }
    }
}

void evaluateNums(_Bool *primes, int* primes_count) {
    for(int i = 2; i <= MAX; i++) {
        *(primes+i) = 1;
    }
    int temp = 0;
    for(int j = 2; j * j <= MAX; j++) {
        if(*(primes+j)) {
            for(int k = j * j; k <= MAX; k += j) {
                if(*(primes+k) != 0) {
                    *(primes+k) = 0;
                    temp++;
                }
            }
        }
    }
    *primes_count = MAX-temp;
}
