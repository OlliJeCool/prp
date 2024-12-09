#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Queue {
    int** data;
    size_t head;
    size_t length;
    size_t capacity;
} queue_t;

queue_t* create_queue();
void delete_queue(queue_t* queue);
bool push_to_queue(queue_t* queue, int* element);
void* pop_from_queue(queue_t* queue);
void* get_from_queue(queue_t* queue, int inx);
int get_queue_size(queue_t* queue);
void print_queue(queue_t* queue);

#endif //QUEUE_H
