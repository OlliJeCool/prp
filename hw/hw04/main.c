#include <stdio.h>
#define MAX 1000000

int takeAndValidateInput(long int *, int *);
void printError(int);
int* generatePrimeArray(int *);
int* calculateInPrimes(int, int*, int);
void printOutput(int*, int*, int);

int main() {
    long int input = 0;
    int ret = 0;
    int primes_count = 0;
    int* primes = generatePrimeArray(&primes_count);
    while(takeAndValidateInput(&input, &ret) == 1) {
        if(!ret) {
            int* powers = calculateInPrimes(input, primes, primes_count);
            printOutput(primes, powers, primes_count);
        }
    }
    return 0;
}

void printOutput(int* primes, int* powers, int count) {
    for(int i = 0; i < count; i++) {
        if(powers[i] != 0) {
            printf(powers[i] == 1 ? "%d x" : "%d^%d"  , primes[i], powers[i]);
        }
    }
}

int* calculateInPrimes(int num, int* primes, int count) {
    int temp = num;
    int nums[count];
    for(int i = count; i >= 0; i--) {
        if(temp % primes[i] == 0) {
            temp = num / primes[i];
            nums[i]++;
            i++;
        }
    }
    return nums;
}

void printError(int ret) {
    if(ret == 100) {
        fprintf(stderr, "Error: Chybny vstup!");
    }
}

int takeAndValidateInput(long int* input, int* ret) {
    int result = scanf("%d", input);
    if(input < 0 || result == 0) {
        *ret = 100;
    }
    return result;
}

void extractPrimes(int* primes_count, int* primesOnly, int* primes) {
    int index = 0;
    for(int i = 0; i < MAX; i++) {
        if(primes[i]) {

        }
    }
}


int* evaluateNums(int* primes_count) {
    _Bool arr[MAX+1];
    for(int i = 2; i <= MAX; i ++) {
        arr[i] = 1;
    }
    for(int j = 2; j * j <= MAX; j++) {
        if(arr[j]) {
            for(int k = j * j; k <= MAX; k += j) {
                if(arr[k] != 0) {
                    arr[k] = 0;
                }
            }
        }
    }

    static int primeOnly[sizeof(arr)-2-*primes_count];
    int index = 0;
    for(int h = 0; h < MAX; h++) {
        if(arr[h]) {
            primeOnly[index++] = h;
        }
    }
    *primes_count = sizeof(arr)-2-*primes_count;
    return primeOnly;
}