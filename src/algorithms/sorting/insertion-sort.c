#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"

void insertion_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
    if (arr == NULL || cmp == NULL) {
        return;
    }

    char *base = arr;

    for (size_t i = 1; i < arrlen; i++) {
        void *key = malloc(item_size);
        memcpy(key, base + (i * item_size), item_size);

        i64 j = i - 1;

        while (cmp(key, base + (j * item_size)) < 0 && j >= 0) {
            memcpy(base + ((j + 1) * item_size), base + (j * item_size),
                   item_size);
            j--;
        }
        memcpy(base + ((j + 1) * item_size), key, item_size);
        free(key);
    }
}
