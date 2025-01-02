#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void bubble_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
    if (arr == NULL || cmp == NULL) {
        return;
    }

    char *base = arr;
    for (size_t i = 0; i < arrlen - 1; i++) {
        for (size_t j = 0; j < arrlen - i - 1; j++) {
            void *n1 = (base + (j * item_size));
            void *n2 = (base + ((j + 1) * item_size));
            if (cmp(n1, n2) > 0) {
                ut_swap(n1, n2, item_size);
            }
        }
    }
}
