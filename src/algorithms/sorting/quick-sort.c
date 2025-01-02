#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"

static u64 _partition(void *arr, u64 left, u64 right, size_t item_size,
                      compare *cmp) {
    char *base = arr;
    i64 pivot = right;
    i64 i = left - 1;

    for (u64 j = left; j < right; j++) {
        if (cmp(base + (j * item_size), base + (pivot * item_size)) < 0) {
            i++;
            ut_swap(base + (i * item_size), base + (j * item_size), item_size);
        }
    }

    ut_swap(base + ((i + 1) * item_size), base + (pivot * item_size),
            item_size);
    return i + 1;
}

static void _quick_sort(void *arr, u64 left, u64 right, size_t item_size,
                        compare *cmp) {
    if (left < right) {
        u64 pivot_index = _partition(arr, left, right, item_size, cmp);
        if (pivot_index > 0)
            _quick_sort(arr, left, pivot_index - 1, item_size, cmp);

        _quick_sort(arr, pivot_index + 1, right, item_size, cmp);
    }
}

void quick_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
    if (arr == NULL || cmp == NULL) {
        return;
    }

    _quick_sort(arr, 0, arrlen - 1, item_size, cmp);
}
