#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

i8 ut_compare_u64(const void *a, const void *b) {
  const u64 _a = *(const u64 *)a;
  const u64 _b = *(const u64 *)b;

  return (_a > _b) - (_a < _b);
}

void ut_swap(void *a, void *b, size_t item_size) {
  char *tmp = malloc(item_size);
  memcpy(tmp, a, item_size);
  memcpy(a, b, item_size);
  memcpy(b, tmp, item_size);
  free(tmp);
}

void ut_print_unsupported(void *arr, size_t arrlen) {
  printf("Elements: unsupported type\n");
}

void ut_print_u64arr(u64 *arr, size_t arrlen) {
  printf("Elements: ");

  for (size_t i = 0; i < arrlen; i++) {
    printf("%lu", arr[i]);

    if (i != arrlen - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void ut_print_strarr(char **arr, size_t arrlen) {
  printf("Elements: ");

  for (size_t i = 0; i < arrlen; i++) {
    printf("%s", arr[i]);

    if (i != arrlen - 1) {
      printf(", ");
    }
  }
  printf("\n");
}
