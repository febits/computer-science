#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "ds/dyrray.h"
#include "ds/maxheap.h"
#include "utils.h"

bool maxheap_init(maxheap *hp, size_t item_size, size_t initial_capacity) {
    if (hp == NULL) {
        return false;
    }

    if (dyrray_init(&hp->dr, item_size, initial_capacity) == false) {
        return false;
    }

    return true;
}

static void _siftup(maxheap *hp, size_t i, compare *cmp) {
    size_t parent = (i - 1) / 2;
    while (i != 0 &&
           cmp(dyrray_get(&hp->dr, i), dyrray_get(&hp->dr, parent)) > 0) {
        dyrray_swap(&hp->dr, i, parent);
        i = parent;
        parent = (i - 1) / 2;
    }
}

static void _siftdown(maxheap *hp, size_t i, compare *cmp) {
    while (true) {
        size_t biggest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < hp->dr.size &&
            cmp(dyrray_get(&hp->dr, left), dyrray_get(&hp->dr, biggest)) > 0) {
            biggest = left;
        }

        if (right < hp->dr.size &&
            cmp(dyrray_get(&hp->dr, right), dyrray_get(&hp->dr, biggest)) > 0) {
            biggest = right;
        }

        if (biggest == i) break;

        dyrray_swap(&hp->dr, i, biggest);

        i = biggest;
    }
}

bool maxheap_heapify(maxheap *hp, void *arr, size_t size, compare *cmp) {
    if (hp == NULL || arr == NULL || cmp == NULL) {
        return false;
    }

    hp->dr.size = size;

    if (size > hp->dr.capacity) {
        hp->dr.capacity = size * 2;
        hp->dr.data = realloc(hp->dr.data, hp->dr.capacity * hp->dr.item_size);

        if (hp->dr.data == NULL) {
            return false;
        }
    }

    memcpy(hp->dr.data, arr, hp->dr.size * hp->dr.item_size);

    for (int i = (hp->dr.size / 2) - 1; i >= 0; i--) {
        _siftdown(hp, i, cmp);
    }

    return true;
}

bool maxheap_push(maxheap *hp, void *data, compare *cmp) {
    if (hp == NULL || data == NULL || cmp == NULL) {
        return false;
    }

    dyrray_push(&hp->dr, data);
    _siftup(hp, hp->dr.size - 1, cmp);

    return true;
}

bool maxheap_pop(maxheap *hp, compare *cmp) {
    if (hp == NULL || cmp == NULL || hp->dr.size == 0) {
        return false;
    }

    dyrray_pop(&hp->dr);
    dyrray_swap(&hp->dr, 0, hp->dr.size);
    _siftdown(hp, 0, cmp);

    return true;
}

void *maxheap_peek(maxheap *hp) {
    if (hp == NULL) {
        return NULL;
    }

    return dyrray_get(&hp->dr, 0);
}

void maxheap_destroy(maxheap *hp) {
    if (hp == NULL) {
        return;
    }

    free(hp->dr.data);
    hp->dr.size = hp->dr.capacity = hp->dr.item_size = 0;
}
