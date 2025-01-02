#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"

typedef enum { FAILED, PASSED } ut_assert_print_type;
typedef i8(compare)(const void *, const void *);

#define ARRSIZE(arr) (sizeof((arr)) / sizeof((arr[0])))
#define UT_GETAS(pointer, type) (*(type)(pointer))

#define ut_assert(expr)                                                        \
  if (expr)                                                                    \
    ut_assert_print(__FILE__, __func__, __LINE__, #expr, PASSED);              \
  else                                                                         \
    ut_assert_print(__FILE__, __func__, __LINE__, #expr, FAILED);

#define error(fmt, ...)                                                        \
  fprintf(stderr, fmt, ##__VA_ARGS__);                                         \
  exit(EXIT_FAILURE);

#define ut_print_array(arr, arrlen)                                            \
  _Generic((*arr),                                                             \
      u64: ut_print_u64arr,                                                    \
      char *: ut_print_strarr,                                                 \
      default: ut_print_unsupported)((arr), (arrlen))

void ut_assert_print(const char *file, const char *func, int line,
                     const char *expr, ut_assert_print_type type);

bool ut_array_sorted(void *arr, size_t arrlen, size_t item_size, compare *cmp);
void ut_swap(void *a, void *b, size_t item_size);
i8 ut_compare_u64(const void *a, const void *b);

void ut_print_unsupported(void *arr, size_t arrlen);
void ut_print_u64arr(u64 *arr, size_t arrlen);
void ut_print_strarr(char **arr, size_t arrlen);

#endif
