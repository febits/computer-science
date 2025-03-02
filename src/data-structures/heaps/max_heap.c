#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "ds/maxheap.h"
#include "utils.h"

#define INITIAL_CAPACITY 5
#define MAXHEAPNULL                                                            \
    (maxheap) { 0, 0, 0, NULL }

bool maxheap_init(maxheap *hp, size_t elemsize) {
    if (hp == NULL) {
        return false;
    }

    *hp = (maxheap){0, INITIAL_CAPACITY, elemsize,
                    malloc(elemsize * INITIAL_CAPACITY)};

    if (hp->data == NULL) {
        *hp = MAXHEAPNULL;
        return false;
    }

    return true;
}

static void _siftup(maxheap *hp, size_t i, compare *cmp) {
    char *base = hp->data;

    size_t parent = (i - 1) / 2;
    while (i != 0 &&
           cmp(base + (hp->elemsize * i), base + (hp->elemsize * parent)) > 0) {
        ut_swap(base + (hp->elemsize * i), base + (hp->elemsize * parent),
                hp->elemsize);
        i = parent;
        parent = (i - 1) / 2;
    }
}

static void _siftdown(maxheap *hp, size_t i, compare *cmp) {
    char *base = hp->data;

    while (true) {
        size_t biggest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < hp->size && cmp(base + (left * hp->elemsize),
                                   base + (biggest * hp->elemsize)) > 0) {
            biggest = left;
        }

        if (right < hp->size && cmp(base + (right * hp->elemsize),
                                    base + (biggest * hp->elemsize)) > 0) {
            biggest = right;
        }

        if (biggest == i) break;

        ut_swap(base + (hp->elemsize * i), base + (hp->elemsize * biggest),
                hp->elemsize);

        i = biggest;
    }
}

bool maxheap_heapify(maxheap *hp, void *arr, size_t size, compare *cmp) {
    if (hp == NULL || arr == NULL || cmp == NULL) {
        return false;
    }

    if (size > hp->capacity) {
        hp->capacity = size * 2;
        hp->data = realloc(hp->data, hp->capacity * hp->elemsize);

        if (hp->data == NULL) {
            return false;
        }
    }

    hp->size = size;
    memcpy(hp->data, arr, hp->size * hp->elemsize);

    for (int i = (hp->size / 2) - 1; i >= 0; i--) {
        _siftdown(hp, i, cmp);
    }

    return true;
}

bool maxheap_push(maxheap *hp, void *data, compare *cmp) {
    if (hp == NULL || data == NULL || cmp == NULL) {
        return false;
    }

    if (hp->size >= hp->capacity) {
        hp->capacity *= 2;
        hp->data = realloc(hp->data, hp->capacity * hp->elemsize);

        if (hp->data == NULL) {
            return false;
        }
    }

    char *base = hp->data;
    memcpy(base + (hp->size++ * hp->elemsize), data, hp->elemsize);
    _siftup(hp, hp->size - 1, cmp);

    return true;
}

bool maxheap_pop(maxheap *hp, compare *cmp) {
    if (hp == NULL || cmp == NULL || hp->size == 0) {
        return false;
    }

    char *base = hp->data;
    ut_swap(base, base + (hp->elemsize * --hp->size), hp->elemsize);
    _siftdown(hp, 0, cmp);

    return true;
}

void *maxheap_peek(maxheap *hp) {
    if (hp == NULL) {
        return NULL;
    }

    return hp->size == 0 ? NULL : hp->data;
}

void maxheap_destroy(maxheap *hp) {
    if (hp == NULL || hp->data == NULL) {
        return;
    }

    hp->size = hp->capacity = 0;
    free(hp->data);
}
