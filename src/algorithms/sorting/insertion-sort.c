#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"

void insertion_sort(void *arr, size_t arrlen, size_t item_size,
                    i8 (*cmp)(const void *, const void *)) {
  if (arr == NULL || cmp == NULL) {
    return;
  }

  char *base = (char *)arr;

  for (size_t i = 1; i < arrlen; i++) {
    void *key = malloc(item_size);
    memcpy(key, base + (i * item_size), item_size);

    i64 j = i - 1;

    while (cmp(key, base + (j * item_size)) < 0 && j >= 0) {
      memcpy(base + ((j + 1) * item_size), base + (j * item_size), item_size);
      j--;
    }
    memcpy(base + ((j + 1) * item_size), key, item_size);
    free(key);
  }
}

int main(void) {
  u64 arr[] = {200, 1, 100, 50, 20, 35, 0, 5, 10, 45, 15};

  ut_print_array(arr, ARRSIZE(arr));
  insertion_sort(arr, ARRSIZE(arr), sizeof(arr[0]), ut_compare_u64);
  ut_print_array(arr, ARRSIZE(arr));

  return EXIT_SUCCESS;
}
