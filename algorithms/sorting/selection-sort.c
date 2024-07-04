#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

void selection_sort(void *arr, size_t arrlen, size_t item_size,
                    i8 (*cmp)(const void *, const void *)) {
  if (arr == NULL || cmp == NULL) {
    return;
  }

  char *base = (char *)arr;

  for (size_t i = 0; i < arrlen - 1; i++) {
    u64 min_index = i;

    for (size_t j = i + 1; j < arrlen; j++) {
      void *n1 = (void *)(base + (j * item_size));
      void *n2 = (void *)(base + (min_index * item_size));
      if (cmp(n1, n2) < 0) {
        min_index = j;
      }
    }

    ut_swap(base + (min_index * item_size), base + (i * item_size), item_size);
  }
}

int main(void) {
  u64 arr[] = {200, 1, 100, 50, 20, 35, 0, 5, 10, 45, 15};

  ut_print_array(arr, ARRSIZE(arr));
  selection_sort(arr, ARRSIZE(arr), sizeof(arr[0]), ut_compare_u64);
  ut_print_array(arr, ARRSIZE(arr));

  return EXIT_SUCCESS;
}
