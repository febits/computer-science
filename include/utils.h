#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#include "types.h"

#define ARRSIZE(arr) (sizeof((arr)) / sizeof((arr[0])))

#define error(fmt, ...)                                                        \
  fprintf(stderr, fmt, ##__VA_ARGS__);                                         \
  exit(EXIT_FAILURE);

#define ut_print_array(arr, arrlen)                                            \
  _Generic((*arr),                                                             \
      u64: ut_print_u64arr,                                                    \
      char *: ut_print_strarr,                                                 \
      default: ut_print_unsupported)((arr), (arrlen))

void ut_swap(void *a, void *b, size_t item_size);
i8 ut_compare_u64(const void *a, const void *b);

void ut_print_unsupported(void *arr, size_t arrlen);
void ut_print_u64arr(u64 *arr, size_t arrlen);
void ut_print_strarr(char **arr, size_t arrlen);

#endif
