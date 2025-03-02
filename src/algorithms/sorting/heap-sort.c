#include <stdlib.h>
#include <string.h>

#include "algorithms/hsort.h"
#include "utils.h"

static void _siftdown(void *arr, size_t arrlen, size_t item_size, compare *cmp,
                      size_t i) {
    char *base = arr;

    while (true) {
        size_t biggest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < arrlen &&
            cmp(base + (left * item_size), base + (biggest * item_size)) > 0) {
            biggest = left;
        }

        if (right < arrlen &&
            cmp(base + (right * item_size), base + (biggest * item_size)) > 0) {
            biggest = right;
        }

        if (biggest == i) break;

        ut_swap(base + (item_size * i), base + (item_size * biggest),
                item_size);

        i = biggest;
    }
}

static void _heapify(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
    for (int i = (arrlen / 2) - 1; i >= 0; i--) {
        _siftdown(arr, arrlen, item_size, cmp, i);
    }
}

void heap_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
    if (arr == NULL || cmp == NULL) {
        return;
    }

    _heapify(arr, arrlen, item_size, cmp);

    char *base = arr;
    for (int i = arrlen - 1; i > 0; i--) {
        ut_swap(base + (i * item_size), base, item_size);
        _siftdown(arr, i, item_size, cmp, 0);
    }
}
