#include <stdio.h>
#define MAX 1000002

int takeAndValidateInput(long long int *, int *);
void printError(int);
void evaluateNums(_Bool*, int *);
void calculateInPrimes(long long int, int*, int*, int);
void printOutput(int*, int*, int,long long int);
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
            if(input == 1) {
                printf("Prvociselny rozklad cisla %lld je:\n1\n", input);
                continue;
            }
            int powers[primes_count];
            calculateInPrimes(input, primeOnly, powers, primes_count);
            printf("Prvociselny rozklad cisla %lld je:\n", input);
            printOutput(primeOnly, powers, primes_count, input);
            continue;
        }
        break;
    }
    printError(ret);
    return ret;
}

void printOutput(int* primes, int* powers, int count, long long int num) {
    _Bool first = 1;
    for(int i = 2; i < count; i++) {
        int power = *(powers+i);
        int prime = *(primes+i);
        if(prime > num) {
            break;
        }
        if(power != 0) {
            if(power == 1) {
                printf(first ? "" : " x ");
                printf("%d", prime);
                first = first ? 0 : first;
                continue;
            }
                printf(first ? "" : " x ");
                printf("%d^%d", prime, power);
                first = first ? 0 : first;
        }
    }
    putchar('\n');
}

void calculateInPrimes(long long int num, int* primeOnly, int* powers, int count) {
    long long int temp = num;
    for(int j = 0; j < count; j++) {
        *(powers+j) = 0;
    }
    for(int i = count-1; i >= 2; i--) {
        int prime = *(primeOnly+i);
        if(temp % prime == 0) {
            temp = temp / prime;
            *(powers+i)+=1;
            i++;
        }
    }
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
    for(int h = 2; h < MAX && index < count; h++) {
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
    *primes_count = MAX-2-temp;
}
