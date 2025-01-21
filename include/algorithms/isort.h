#ifndef ISORT_H
#define ISORT_H

#include "utils.h"
#include <stddef.h>

void insertion_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp);

#endif
