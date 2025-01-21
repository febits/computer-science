#ifndef SSORT_H
#define SSORT_H

#include "utils.h"
#include <stddef.h>

void selection_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp);

#endif
