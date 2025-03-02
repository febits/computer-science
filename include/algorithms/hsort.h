#ifndef HSORT_H
#define HSORT_H

#include <stddef.h>

#include "utils.h"

void heap_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp);

#endif
