#ifndef BSEARCH_H
#define BSEARCH_H

#include "utils.h"
#include <stdbool.h>

bool binary_search(void *arr, size_t arrlen, size_t item_size, void *target,
                   compare *cmp);

#endif
