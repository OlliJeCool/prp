#include "queue.h"

#include <stdio.h>


queue_t* create_queue(int capacity) {
    queue_t* queue = malloc(sizeof(queue_t));
    if (!queue) return NULL;
    void** queue_data = malloc(sizeof(void*) * capacity);
    if (!queue_data) return NULL;
    queue->data = queue_data;
    queue->head = 0;
    queue->length = 0;
    return queue;
}

bool push_to_queue(queue_t* queue, int* element) {
    print_queue(queue);
    int new_index = (queue->head + queue->length++)%queue->capacity;
    if (queue->data[new_index] != NULL) {
        return false;
    }
    queue->data[new_index] = element;
    print_queue(queue);
    return true;
}

void* pop_from_queue(queue_t* queue) {
    print_queue(queue);
    void* element = queue->data[queue->head];
    queue->data[queue->head] = NULL;
    queue->head = (queue->head+1)% queue->capacity;
    queue->length--;
    print_queue(queue);
    return element;
}

void* get_from_queue(queue_t* queue, int idx) {
    return queue->data[(queue->head+idx)%queue->capacity];
}

int get_queue_size(queue_t* queue) {
    return queue->length;
}

void delete_queue(queue_t* queue) {
    free(queue->data);
    free(queue);
}

void print_queue(queue_t* queue) {
    putchar('[');
    for (int i = 0; i < queue->capacity; i++) {
        printf("%d", queue->data[i]);
        if (i != queue->length -1) {
            printf(", ");
        }
    }
    putchar(']\n');

}