#include <stdlib.h>
#define QUEUESTACK_H_GUARD

struct queue_stack* create(int* return_status);
void delete(struct queue_stack* self, int* return_status);
void add(struct queue_stack* self, void* payload, int* return_status);
void* pop(struct queue_stack* self, int* return_status);
void* peek(struct queue_stack* self, int* return_status);

typedef struct Node{
    struct Node* prev;
    struct Node* next;
    void* payload;
} Node;

struct queue_stack {
    Node* head;
    Node* tail;
    size_t size;
};
