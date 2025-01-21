#ifndef LSEARCH_H
#define LSEARCH_H

#include "utils.h"
#include <stdbool.h>

bool linear_search(void *arr, size_t arrlen, size_t item_size, void *target,
                   compare *cmp);

#endif
