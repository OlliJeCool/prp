#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define START_CAPACITY 8

typedef struct line {
    char* data;
    size_t length;
} line;

typedef struct line_list {
    line** lines;
    size_t count;
} line_list;

line* load_line(FILE*);
line_list* load_lines(FILE*);
void free_lines(line_list*);
int lookup(line , line* );
line to_line(char* pattern);

int main(int argc, char* argv[]) {
    if (argc > 3) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE* file = NULL;
    if(argc > 2) {
        file = fopen(argv[2], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
    } else {
        file = stdin;
    }

    line_list* lines = load_lines(file);
    fclose(file);

    if (!lines) {
        fprintf(stderr, "Error: Failed to load lines.\n");
        return 1;
    }
    line pattern = to_line(argv[1]);
    _Bool found = false;
    for (size_t i = 0; i < lines->count; i++) {
        if(lookup(pattern, lines->lines[i]) == 0) {
            found = true;
            printf("%s\n", lines->lines[i]->data);
        }
    }

    free_lines(lines);
    return !found;
}

line* load_line(FILE* file) {
    char* nline;
    if(!(nline = malloc(START_CAPACITY))) return NULL;
    int length = 0, capacity = START_CAPACITY;
    for(char c; (c = fgetc(file)) != EOF;) {
        if(length+1 >= capacity) {
            capacity *= 2;
            char* ecline;
            if((ecline = realloc(nline, capacity)) == NULL) {
                free(nline);
                return NULL;
            }
            nline = ecline;
        }
        if(c == '\n') break;
        nline[length++] = c;
    }
    if(length == 0 && feof(file)) {
        free(nline);
        return NULL;
    }

    char* fcLine;
    if((fcLine = realloc(nline, length+1)) == NULL) {
        free(nline);
        return NULL;
    }
    nline = fcLine;
    nline[length] = '\0';
    line* fLine;
    if((fLine = malloc(sizeof(line))) == NULL) {
        free(nline);
        return NULL;
    }
    fLine->data = nline;
    fLine->length = length;
    return fLine;
}

line_list* load_lines(FILE* file) {
    line** data;
    if(!(data = malloc(sizeof(line*)*START_CAPACITY))) return NULL;

    int count = 0, capacity = START_CAPACITY;
    for(line* l; (l = load_line(file)) != NULL; ) {
        if(count >= capacity) {
            capacity*= 2;
            line** ndata;
            if(!(ndata = realloc(data, capacity*sizeof(line*)))) {
                free(data);
                return NULL;
            }
            data = ndata;
        }
        data[count++] = l;
    }
    line** fdata;
    if(!(fdata = realloc(data, (count+1)*sizeof(line*)))) {
        free(data);
        return NULL;
    }
    data = fdata;
    line_list* list;
    if(!(list = malloc(sizeof(line_list)))) {
        for(int i = 0; i < count; i++) {
            free(data[i]->data);
            free(data[i]);
        }
        free(data);
        return NULL;
    }
    list->lines = data;
    list->count = count;
    return list;
}

line to_line(char* pattern) {
    int length=-1;
    while(pattern[length++] != '\0');
    return (line){pattern, length};
}

int lookup(line pattern, line* line) {
    int count = 0, index = 0;
    for(int i = 0; i < line->length; i++) {
        if(line->data[i] == pattern.data[index]) {
            if(count == pattern.length-1) {
                return 0;
            }
            count+=1;
            index+=1;
        }
        else {
            index = 0;
            count = 0;
        }
    }
    return 1;
}

int a_lookup(line pattern, line* line) {
    int index = 0;
    for(int i = 0; i < line->length; i++) {

        if(pattern.data[index] == '?' && i > 0) {

        }
    }
}

void free_lines(line_list* list) {
    if (list == NULL) return;
    for (size_t i = 0; i < list->count; i++) {
        free(list->lines[i]->data);
        free(list->lines[i]);
    }
    free(list->lines);
    free(list);
}
