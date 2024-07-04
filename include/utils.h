#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#include "types.h"

#define error(fmt, ...)                                                        \
  fprintf(stderr, fmt, ##__VA_ARGS__);                                         \
  exit(EXIT_FAILURE);

#define ARRSIZE(arr) (sizeof((arr)) / sizeof((arr[0])))

i8 ut_compare_u64(const void *a, const void *b);
void ut_print_array(u64 *arr, size_t arrlen);
void ut_print_strarr(const char **arr, size_t arrlen);
void ut_swap(void *a, void *b, size_t item_size);

#endif
