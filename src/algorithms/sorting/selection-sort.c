#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

void selection_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
    if (arr == NULL || cmp == NULL) {
        return;
    }

    char *base = arr;

    for (size_t i = 0; i < arrlen - 1; i++) {
        u64 min_index = i;

        for (size_t j = i + 1; j < arrlen; j++) {
            void *n1 = (base + (j * item_size));
            void *n2 = (base + (min_index * item_size));
            if (cmp(n1, n2) < 0) {
                min_index = j;
            }
        }

        ut_swap(base + (min_index * item_size), base + (i * item_size),
                item_size);
    }
}
