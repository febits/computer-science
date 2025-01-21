#ifndef MSORT_H
#define MSORT_H

#include "utils.h"
#include <stddef.h>

void merge_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp);

#endif
