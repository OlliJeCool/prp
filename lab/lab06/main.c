#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 8

char* read_line();

int main(){
    char * the_line = read_line();
    printf("%s\n", the_line);
    free(the_line);
    return 0;
}

char* read_line(){
    char *line = malloc(START_SIZE * sizeof(char));
    if(line == NULL){
        return NULL;
    }
    int capacity = START_SIZE;
    int length = 0;

    for(char c; (c = getchar()) > '\n' ;){
        if(length == capacity){
        capacity *= 2;
        char * line_new = realloc(line, capacity);
        if(line_new == NULL){
            free(line);
            return NULL;
        }
        line = line_new;
        }
        line[length++] = c;
        printf("Loaded %c, Cap %lu, Used %lu.\n", c, (long int)capacity, (long int)length);
    }
    char* temp_line = realloc(line, length+1);
    if(temp_line == NULL){
        free(line);
        return NULL;
    }
    line = temp_line;
    printf("%d\n", length+1);
    return line;
}
