#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 10

typedef struct {
    char * data;
    size_t length;
} string;

string* read_line(int*);
int takeAndValidateInput(string**,string**);
void printError(int);
char rotate(char, int);

int main(void) {
    char a = rotate('a', 2);

    /*string* cypherText = NULL;
    string* interceptedText = NULL;
    int ret = takeAndValidateInput(&cypherText, &interceptedText);
    if(ret == 0) {
    }
    else {
        printError(ret);
    }

    return ret;
    */
}

void printError(int errCode) {
    switch (errCode) {
        case 100:
            fprintf(stderr, "Error: Chybny vstup!");
            break;
        case 101:
            fprintf(stderr, "Error: Chybna delka vstupu!");
            break;
    }
}

int takeAndValidateInput(string** cT, string** iT) {
    int ret = 0;
    *cT = read_line(&ret);
    *iT = read_line(&ret);
    if(*cT != NULL && *iT != NULL) {
        if((*cT)->length != (*iT)->length) {
            ret = ret == 0 ? 101 : 100;
        }
    }
    return ret;
}

string * read_line(int* ret) {
    char *line;
    if((line = (char*)malloc(START_SIZE*sizeof(char))) == NULL){
        return NULL;
    }
    int capacity = START_SIZE;
    int length = 0;

    for(char c; (c = getchar()) != '\n'; ) {
        if((c<='Z' && c >= 'A') || (c<='z' && c>='a')) {
            if(length>=capacity) {
                capacity *= 2;
                char* new_line;
                if((new_line = (char*)realloc(line, capacity)) == NULL) {
                    free(line);
                    return NULL;
                }
                line = new_line;
            }
        }
        else {
            *ret = 100;
        }
        line[length++] = c;
    }

    char * temp_line;
    if((temp_line = (char*)realloc(line, length+1)) == NULL) {
        free(line);
        return NULL;
    }
    line = temp_line;
    string * finalLine;
    if((finalLine = (string*)malloc(sizeof(string))) == NULL) {
        free(line);
        return NULL;
    }
    line[length] = '\0';
    finalLine->data = line;
    finalLine->length = length;
    return finalLine;
}