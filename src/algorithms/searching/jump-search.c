#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utils.h"

bool jump_search(void *arr, size_t arrlen, size_t item_size, void *target,
                 compare *cmp) {
    if (arr == NULL || cmp == NULL || target == NULL) {
        return false;
    }

    char *base = arr;

    size_t step = sqrt(arrlen);
    size_t curr = 0;
    size_t prev = 0;

    while (curr < arrlen && cmp(base + (curr * item_size), target) < 0) {
        prev = curr;
        curr += step;
        if (curr > arrlen - 1) {
            curr = arrlen;
        }
    }

    for (size_t i = prev; i <= curr; i++) {
        if (cmp(base + (i * item_size), target) == 0) {
            return true;
        }
    }

    return false;
}
