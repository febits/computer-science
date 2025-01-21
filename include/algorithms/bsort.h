#ifndef BSORT_H
#define BSORT_H

#include "utils.h"
#include <stddef.h>

void bubble_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp);

#endif
