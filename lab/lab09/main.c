#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_CAPACITY 8

void hello_world(int);
int str_len(char*, int);
void revert();
char* take_string();
void revert_h(char*);

int main() {
    revert();
    putchar('\n');
    char* str = take_string();
    revert_h(str);
}


void hello_world(int n) {
    if (n == 0) {
        printf("call: %d, hello world\n", n);
        return;
    }
    hello_world(n - 1);
    printf("call: %d, hello world\n", n);
}

void revert() {
    char c;
    if ((c=getchar()) == '\n') {
        return;
    }
    revert();
    putchar(c);
}

int str_len(char* s, int len) {
    if (s[len] == '\0') {
        return len;
    }
    return str_len(s, len+1);
}

void revert_h(char* s) {
    int len = str_len(s, 0);
    for (int i = len-1; i >= 0; i--) {
        putchar(s[i]);
    }
    putchar('\n');
}

char* take_string() {
    int capactiy = START_CAPACITY, length = 0;
    char* out;
    if ((out = (char*)malloc(capactiy)) == NULL) {
        return NULL;
    }
    for (char c; (c = getchar()) != '\n'; ) {
        if (length == capactiy) {
            capactiy *= 2;
            char* new_out;
            if ((new_out = (char*)realloc(out, capactiy)) == NULL) {
                free(out);
                return NULL;
            }
            out = new_out;
        }
        out[length++] = c;
    }
    char* new_out;
    if ((new_out = (char*)realloc(out, length+1)) == NULL) {
        free(out);
        return NULL;
    }
    out = new_out;
    out[length] = '\0';
    return out;
}