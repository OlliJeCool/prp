#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 8

typedef struct {
    char ** memory;
    size_t capacity;
    size_t length;
} loaded_lines;


char* read_line();
loaded_lines read_lines();

int main(){
    loaded_lines lines = read_lines();
    return 0;
}

char* read_line(){
    char *line = malloc(START_SIZE * sizeof(char));
    if(line == NULL){
        return NULL;
    }
    int capacity = START_SIZE;
    int length = 0;

    for(char c; (c = getchar()) != '\n' ;){
        if(c == EOF){
            if(length > 0){
                break;
            }
            else{
            return NULL;
            }
        }
        if(length >= capacity){
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
    printf("Final used: %d\n", length+1);
    return line;
}

loaded_lines read_lines(){
    loaded_lines ll;
    ll.capacity = START_SIZE;
    ll.length = 0;
    ll.memory = malloc(sizeof(char*));
    if(ll.memory == NULL){
        return NULL;
    }
    for(char* line; (line = read_line()) != NULL;){
        if(ll.length*sizeof(char*) >= ll.capacity){
            ll.capacity *= 2;
            char** new_lines = realloc(ll.memory, ll.capacity);
            if(new_lines == NULL){
                for(int i = 0; i < ll.length; i++){
                    free(ll.memory[i]);
                }
                free(ll.memory);
                return NULL;
            }
            ll.memory = new_lines;
        }
        ll.memory[ll.length++] = line;
        printf("Loaded %p, Cap %lu, Used %lu.\n", line, (long int)ll.capacity, (long int)ll.length);
    }
    printf("Final cap: %lu\n", (ll.capacity));
    return ll;

}
