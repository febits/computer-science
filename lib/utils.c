#include <stdio.h>

#include "types.h"

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
