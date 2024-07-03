#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

void ut_swap(void *a, void *b, size_t item_size) {
  char *tmp = malloc(item_size);
  memcpy(tmp, a, item_size);
  memcpy(a, b, item_size);
  memcpy(b, tmp, item_size);
  free(tmp);
}

void ut_print_array(u64 *arr, size_t arrlen) {
  printf("Elements: ");

  for (size_t i = 0; i < arrlen; i++) {
    printf("%lu", arr[i]);

    if (i != arrlen - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void ut_print_strarr(const char **arr, size_t arrlen) {
  printf("Elements: ");

  for (size_t i = 0; i < arrlen; i++) {
    printf("%s", arr[i]);

    if (i != arrlen - 1) {
      printf(", ");
    }
  }
  printf("\n");
}
