#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stddef.h>
#include <stdbool.h>

#include "utils.h"

typedef struct {
    size_t size;
    size_t capacity;
    size_t elemsize;
    void *data;
} maxheap;

bool maxheap_init(maxheap *hp, size_t elemsize);

bool maxheap_heapify(maxheap *hp, void *arr, size_t size, compare *cmp);
bool maxheap_push(maxheap *hp, void *data, compare *cmp);
bool maxheap_pop(maxheap *hp, compare *cmp);
void* maxheap_peek(maxheap *hp);

void maxheap_destroy(maxheap *hp);

#endif
