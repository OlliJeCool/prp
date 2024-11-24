#include "queuestack.h"
#include <stdlib.h>

struct queue_stack* create(int* return_status){
    struct queue_stack* ret;
    if((ret = malloc(sizeof(struct queue_stack))) == NULL){
        *return_status = -1;
        return NULL;
    }
    ret->head = NULL;
    ret->tail = NULL;
    ret->size = 0;
    return ret;
};

void delete(struct queue_stack* self, int* return_status);
void add(struct queue_stack* self, void* payload, int* return_status){
    struct Node* element;
    if((element = malloc(sizeof(struct node*))) == NULL){
       *return_status = -1;
       return;
    }
    element->prev = self->tail;
    element->next = NULL;
    element->payload = payload;

    if(self->head == NULL){
        self->head = element;
    }
    self->tail = element;
    self->size ++;
}

void* pop(struct queue_stack* self, int* return_status){
    if(self == NULL){
        *return_status = -2;
        return NULL;
    }
    if(self->size == 0){
        *return_status = -2;
        return NULL;
    }
    struct Node * element = self->head;
    self->head = element->next;
    self->size --;
    free(element);

    *return_status = 0;
    return element->payload;
}

void* peek(struct queue_stack* self, int* return_status);
