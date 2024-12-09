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
int lookup(line, line*, bool);
line to_line(char* pattern);
void colorize_and_print(const char* text, const char* pattern, bool use_regex);
size_t str_len(const char* str);
bool is_flag(const char* arg, const char* flag);
void print_colored(const char* text, int start, int length);

int main(int argc, char* argv[]) {
    bool use_regex = false;
    bool colorize = false;
    char* pattern_arg = NULL;
    char* filename = NULL;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (is_flag(argv[i], "-E")) {
            use_regex = true;
        } else if (is_flag(argv[i], "--color=always")) {
            colorize = true;
        } else if (pattern_arg == NULL) {
            pattern_arg = argv[i];
        } else {
            filename = argv[i];
        }
    }

    if (pattern_arg == NULL) {
        fprintf(stderr, "Usage: %s [-E] [--color=always] <pattern> [filename]\n", argv[0]);
        return 1;
    }

    FILE* file = filename ? fopen(filename, "r") : stdin;
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    line_list* lines = load_lines(file);
    if (filename) fclose(file);

    if (!lines) {
        fprintf(stderr, "Error: Failed to load lines.\n");
        return 1;
    }

    line pattern = to_line(pattern_arg);
    _Bool found = false;

    for (size_t i = 0; i < lines->count; i++) {
        if (lookup(pattern, lines->lines[i], use_regex) == 0) {
            found = true;
            if (colorize) {
                colorize_and_print(lines->lines[i]->data, pattern_arg, use_regex);
            } else {
                printf("%s\n", lines->lines[i]->data);
            }
        }
    }

    free_lines(lines);
    return !found;
}

size_t str_len(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') length++;
    return length;
}

bool is_flag(const char* arg, const char* flag) {
    size_t i = 0;
    while (arg[i] == flag[i] && arg[i] != '\0' && flag[i] != '\0') i++;
    return arg[i] == '\0' && flag[i] == '\0';
}

line* load_line(FILE* file) {
    char* nline;
    if (!(nline = malloc(START_CAPACITY))) return NULL;
    int length = 0, capacity = START_CAPACITY;
    for (char c; (c = fgetc(file)) != EOF;) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* ecline;
            if ((ecline = realloc(nline, capacity)) == NULL) {
                free(nline);
                return NULL;
            }
            nline = ecline;
        }
        if (c == '\n') break;
        nline[length++] = c;
    }
    if (length == 0 && feof(file)) {
        free(nline);
        return NULL;
    }

    nline[length] = '\0'; // Ensure null-termination
    line* fLine = malloc(sizeof(line));
    if (!fLine) {
        free(nline);
        return NULL;
    }
    fLine->data = nline;
    fLine->length = length;
    return fLine;
}

line_list* load_lines(FILE* file) {
    line** data = malloc(sizeof(line*) * START_CAPACITY);
    if (!data) return NULL;

    int count = 0, capacity = START_CAPACITY;
    for (line* l; (l = load_line(file)) != NULL;) {
        if (count >= capacity) {
            capacity *= 2;
            line** ndata = realloc(data, capacity * sizeof(line*));
            if (!ndata) {
                free(data);
                return NULL;
            }
            data = ndata;
        }
        data[count++] = l;
    }
    line_list* list = malloc(sizeof(line_list));
    if (!list) {
        for (int i = 0; i < count; i++) {
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
    size_t length = str_len(pattern);
    return (line){pattern, length};
}

int lookup(line pattern, line* text_line, bool use_regex) {
    size_t pat_len = pattern.length;
    size_t text_len = text_line->length;
    size_t i = 0, j = 0;

    while (i < text_len) {
        if (j < pat_len && (pattern.data[j] == '.' || pattern.data[j] == text_line->data[i])) {
            // Match any character (.) or exact match
            i++;
            j++;
        } else if (j < pat_len && pattern.data[j] == '?') {
            // '?' Matches zero or one of the preceding character
            j++;
        } else if (j + 1 < pat_len && pattern.data[j + 1] == '*') {
            // '*' Matches zero or more of the preceding character
            if (j < pat_len && (pattern.data[j] == '.' || pattern.data[j] == text_line->data[i])) {
                i++;
            } else {
                j += 2;
            }
        } else if (j < pat_len && pattern.data[j] == '*') {
            // Handle stray '*' without a preceding character
            i++;
        } else {
            // No match, reset pattern pointer and move to next text character
            i = i - j + 1; // Move `i` back to next possible starting position
            j = 0;         // Reset pattern pointer
        }

        // If we've matched the entire pattern, return success
        if (j == pat_len) return 0;
    }

    return 1; // No match found
}


void print_colored(const char* text, int start, int length) {
    for (int i = 0; i < start; i++) putchar(text[i]);
    printf("\033[31m"); // Red color
    for (int i = start; i < start + length; i++) putchar(text[i]);
    printf("\033[0m"); // Reset color
    for (int i = start + length; text[i] != '\0'; i++) putchar(text[i]);
    putchar('\n');
}

void colorize_and_print(const char* text, const char* pattern, bool use_regex) {
    size_t pat_len = str_len(pattern);
    size_t text_len = str_len(text);

    for (size_t i = 0; i <= text_len - pat_len; i++) {
        size_t match_len = 0;
        for (size_t j = 0; j < pat_len; j++) {
            char pc = pattern[j];
            char tc = text[i + j];

            if (use_regex && pc == '.') {
                match_len++;
            } else if (tc == pc) {
                match_len++;
            } else {
                break;
            }
        }
        if (match_len == pat_len) {
            print_colored(text, i, pat_len);
            return;
        }
    }
    printf("%s\n", text);
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
