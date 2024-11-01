#include <stdio.h>
#define MAX 1000000

int takeAndValidateInput(long int *, int *);
void printError(int);
void evaluateNums(_Bool*, int *);
void calculateInPrimes(int, _Bool*, int*, int);
void printOutput(_Bool*, int*, int);
void extractPrimes(int*, _Bool*);


int main() {
    long int input = 0;
    int ret = 0, primes_count = 0;
    _Bool primes[MAX+1];
    evaluateNums(primes, &primes_count);
    int primeOnly[primes_count];
    extractPrimes(primeOnly, primes);
    while(takeAndValidateInput(&input, &ret) == 1) {
        printf("count: %d", primes_count);
        printf("ret: %d", ret);
        if(!ret) {
            int powers[primes_count];
            calculateInPrimes(input, primes, powers, primes_count);
            printOutput(primes, powers, primes_count);
        }
    }
    return 0;
}

void printOutput(_Bool* primes, int* powers, int count) {
    for(int i = 0; i < count; i++) {
        if(powers[i] != 0) {
            printf(powers[i] == 1 ? "%d" : "x %d^%d"  , primes[i], powers[i]);
        }
    }
}

void calculateInPrimes(int num, _Bool* primes, int* powers, int count) {
    int temp = num;
    for(int i = count; i >= 0; i--) {
        if(temp % primes[i] == 0) {
            temp = num / primes[i];
            powers[i]++;
            i++;
        }
    }
}

void printError(int ret) {
    if(ret == 100) {
        fprintf(stderr, "Error: Chybny vstup!");
    }
}

int takeAndValidateInput(long int* input, int* ret) {
    int result = scanf("%ld", input);
    if(input < 0 || result == 0) {
        *ret = 100;
    }
    return result;
}

void extractPrimes(int* primeOnly, _Bool* primes) {
    int index = 0;
    for(int h = 0; h < MAX; h++) {
        if(*(primes+h)) {
            index++;
            *(primeOnly+index) = h;
        }
    }
}


void evaluateNums(_Bool *primes, int* primes_count) {
    for(int i = 2; i <= MAX; i ++) {
        *(primes+i) = 1;
    }
    for(int j = 2; j * j <= MAX; j++) {
        if(*(primes+j)) {
            *primes_count += 1;
            for(int k = j * j; k <= MAX; k += j) {
                if(*(primes+k) != 0) {
                    *(primes+k) = 0;
                }
            }
        }
    }
}
