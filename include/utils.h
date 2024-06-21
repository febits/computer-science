#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#include "types.h"

#define ARRSIZE(arr) sizeof(arr) / sizeof(arr[0])

void ut_print_array(u64 *arr, size_t arrlen);

#endif
