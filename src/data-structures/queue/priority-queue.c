#include <stdbool.h>
#include <stdlib.h>

#include "ds/maxheap.h"
#include "ds/pqueue.h"
#include "utils.h"

bool pqueue_init(pqueue *pq, size_t item_size, size_t initial_capacity) {
    if (pq == NULL) {
        return false;
    }

    if (maxheap_init(&pq->hp, item_size, initial_capacity) == false) {
        return false;
    }

    return true;
}

bool pq_enqueue(pqueue *pq, void *data, compare *cmp) {
    if (pq == NULL || data == NULL || cmp == NULL) {
        return false;
    }

    if (maxheap_push(&pq->hp, data, cmp) == false) {
        return false;
    }

    return true;
}

bool pq_dequeue(pqueue *pq, compare *cmp) {
    if (pq == NULL || cmp == NULL) {
        return false;
    }

    if (maxheap_pop(&pq->hp, cmp) == false) {
        return false;
    }

    return true;
}

void *pq_front(pqueue *pq) {
    if (pq == NULL) {
        return false;
    }

    return maxheap_peek(&pq->hp);
}

bool pq_isempty(pqueue *pq) {
    if (pq == NULL) {
        return false;
    }

    return pq->hp.dr.size == 0;
}

void pqueue_destroy(pqueue *pq) {
    if (pq == NULL) {
        return;
    }

    maxheap_destroy(&pq->hp);
}
