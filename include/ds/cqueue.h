#ifndef CQUEUE_H
#define CQUEUE_H

#include <stdbool.h>
#include <stddef.h>

#include "types.h"

typedef struct {
    size_t capacity;
    size_t elemsize;
    size_t size;

    u64 front;
    u64 rear;
    void *data;
} cqueue;

bool cqueue_init(cqueue *cq, size_t capacity, size_t elemsize);

bool cq_enqueue(cqueue *cq, void *data);
bool cq_dequeue(cqueue *cq);

void *cq_front(cqueue *cq);
void *cq_rear(cqueue *cq);

bool cq_isempty(cqueue *cq);
bool cq_isfull(cqueue *cq);

void cqueue_destroy(cqueue *cq);

#endif
