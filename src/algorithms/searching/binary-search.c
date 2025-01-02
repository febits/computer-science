#include <stdbool.h>
#include <stdlib.h>

#include "utils.h"

bool binary_search(void *arr, size_t arrlen, size_t item_size, void *target,
                   compare *cmp) {
    if (arr == NULL || target == NULL || cmp == NULL) {
        return false;
    }

    size_t left = 0;
    size_t right = arrlen - 1;
    char *base = arr;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        void *mid_element = base + (mid * item_size);

        if (cmp(target, mid_element) < 0) {
            right = mid - 1;
        } else if (cmp(target, mid_element) > 0) {
            left = mid + 1;
        } else {
            return true;
        }
    }

    return false;
}
