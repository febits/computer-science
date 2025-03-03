#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "ds/cqueue.h"

#define CQUEUENULL                                                             \
    (cqueue) { 0, 0, 0, 0, 0, NULL }

bool cqueue_init(cqueue *cq, size_t capacity, size_t elemsize) {
    if (cq == NULL) {
        return false;
    }

    *cq = (cqueue){capacity, elemsize, 0, 0, 0, malloc(capacity * elemsize)};

    if (cq->data == NULL) {
        *cq = CQUEUENULL;
        return false;
    }

    return true;
}

bool cq_isfull(cqueue *cq) {
    if (cq == NULL) {
        return false;
    }

    return cq->size == cq->capacity;
}

bool cq_isempty(cqueue *cq) {
    if (cq == NULL) {
        return false;
    }

    return cq->size == 0;
}

bool cq_enqueue(cqueue *cq, void *data) {
    if (cq == NULL || cq_isfull(cq)) {
        return false;
    }

    if (!cq_isempty(cq)) {
        cq->rear = (cq->rear + 1) % cq->capacity;
    }

    char *base = cq->data;
    memcpy(base + (cq->rear * cq->elemsize), data, cq->elemsize);
    cq->size++;

    return true;
}

bool cq_dequeue(cqueue *cq) {
    if (cq == NULL || cq_isempty(cq)) {
        return false;
    }

    cq->front = (cq->front + 1) % cq->capacity;
    cq->size--;

    return true;
}

void *cq_front(cqueue *cq) {
    if (cq == NULL) {
        return NULL;
    }

    char *base = cq->data;
    return base + (cq->front * cq->elemsize);
}

void *cq_rear(cqueue *cq) {
    if (cq == NULL) {
        return NULL;
    }

    char *base = cq->data;
    return base + (cq->rear * cq->elemsize);
}

void cqueue_destroy(cqueue *cq) {
    if (cq == NULL) {
        return;
    }

    cq->rear = cq->front = cq->size = cq->capacity = 0;
    free(cq->data);
}
