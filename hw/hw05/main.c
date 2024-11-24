#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_SIZE 10
#define WRONG_INPUT_ERROR 100
#define WRONG_INPUT_LENGTH_ERROR 101
#define CHAR_COUNT 52

typedef struct {
    char* data;
    size_t length;
} string;

string read_line(int*);
int takeAndValidateInput(string*,string*);
void printError(int);
char rotate(char, int);
string shift(string, int);
string findBestMatch(string, string);
int countSameChars(string, string);
void free_string(string*);

int main(void) {
    string cypherText = {NULL, 0}, interceptedText = {NULL, 0};
    int ret = takeAndValidateInput(&cypherText, &interceptedText);
    if(ret == 0) {
        string final = findBestMatch(cypherText, interceptedText);
        printf("%s\n", final.data);
        free_string(&final);
    }
    else {
        printError(ret);
    }
    free_string(&cypherText);
    free_string(&interceptedText);
    return ret;
}

int countSameChars(string sT, string iT) {
    int count = 0;
    for(int i = 0; i < sT.length; i++) {
        if(sT.data[i] == iT.data[i]) {
            count++;
        }
    }
    return count;
}

string findBestMatch(string cT, string iT) {
    int highest = 0, temp;
    string output = {NULL, 0};
    for(int i = 1; i <= CHAR_COUNT; i++) {
        string shiftedText = shift(cT, i);
        if((temp = countSameChars(shiftedText, iT)) > highest) {
            highest = temp;
            free_string(&output);
            output = shiftedText;
        }
        else {
            free_string(&shiftedText);
        }
    }
    return output;
}

string shift(string input, int offset) {
    const unsigned int length = input.length;
    char* output;
    if((output = malloc(length+1)) == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < length; i++) {
        output[i] = rotate(input.data[i], offset);
    }
    output[length] = '\0';
    string outtext =  { .data = output, .length = length };
    return outtext;
}

char rotate(char c, int offset) {
    static char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    offset %= CHAR_COUNT;
    const char* position = strchr(alphabet, c);
    if(position) {
        int index = position-alphabet;
        char out = alphabet[(index+offset)%CHAR_COUNT];
        return out;
    }
    return c;
}

void printError(int errCode) {
    switch (errCode) {
        case WRONG_INPUT_ERROR:
            fprintf(stderr, "Error: Chybny vstup!\n");
            break;
        case WRONG_INPUT_LENGTH_ERROR:
            fprintf(stderr, "Error: Chybna delka vstupu!\n");
            break;
    }
}

int takeAndValidateInput(string* cT, string* iT) {
    int ret = 0;
    *cT = read_line(&ret);
    *iT = read_line(&ret);

    if(cT->length != iT->length) {
        ret = ret == 0 ? WRONG_INPUT_LENGTH_ERROR : WRONG_INPUT_ERROR;
    }
    return ret;
}

string read_line(int* ret) {
    char *line;
    if((line = (char*)malloc(START_SIZE)) == NULL){
        exit(EXIT_FAILURE);
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
                    exit(EXIT_FAILURE);
                }
                line = new_line;
            }
        }
        else {
            *ret = WRONG_INPUT_ERROR;
        }
        line[length++] = c;
    }

    char * temp_line;
    if((temp_line = (char*)realloc(line, length+1)) == NULL) {
        free(line);
        exit(EXIT_FAILURE);
    }
    line = temp_line;
    string finalLine = { .data=line, .length = length };
    return finalLine;
}

void free_string(string* s) {
    if(s->data != NULL) {
        free(s->data);
        s->data = NULL;
        s->length = 0;
    }
}
