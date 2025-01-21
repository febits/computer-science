#ifndef QSORT_H
#define QSORT_H

#include "utils.h"
#include <stddef.h>

void quick_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp);

#endif
