#ifndef PQUEUE_H
#define PQUEUE_H

#include "ds/maxheap.h"
#include "utils.h"

typedef struct {
    maxheap hp;
} pqueue;

bool pqueue_init(pqueue *pq, size_t elemsize);

bool pq_enqueue(pqueue *pq, void *data, compare *cmp);
bool pq_dequeue(pqueue *pq, compare *cmp);
bool pq_isempty(pqueue *pq);
void *pq_front(pqueue *pq);

void pqueue_destroy(pqueue *pq);

#endif
