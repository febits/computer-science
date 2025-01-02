#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

bool linear_search(void *arr, size_t arrlen, size_t item_size, void *target,
                   compare *cmp) {
    if (arr == NULL || target == NULL || cmp == NULL) {
        return false;
    }

    char *base = arr;
    for (size_t i = 0; i < arrlen; i++) {
        if (cmp(target, (base + (i * item_size))) == 0) {
            return true;
        }
    }

    return false;
}
