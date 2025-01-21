#ifndef JSEARCH_H
#define JSEARCH_H

#include "utils.h"
#include <stdbool.h>

bool jump_search(void *arr, size_t arrlen, size_t item_size, void *target,
                 compare *cmp);

#endif
