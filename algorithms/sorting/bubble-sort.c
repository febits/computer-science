#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"

static i8 _compare(const void *a, const void *b) {
  const u64 _a = *(const u64 *)a;
  const u64 _b = *(const u64 *)b;

  return (_a > _b) - (_a < _b);
}

void bubble_sort(void *arr, size_t arrlen, size_t item_size,
                 i8 (*cmp)(const void *, const void *)) {
  if (arr == NULL || cmp == NULL) {
    return;
  }

  char *base = (char *)arr;
  for (size_t i = 0; i < arrlen - 1; i++) {
    for (size_t j = 0; j < arrlen - i - 1; j++) {
      void *n1 = (void *)(base + (j * item_size));
      void *n2 = (void *)(base + ((j + 1) * item_size));
      if (cmp(n1, n2) > 0) {
        ut_swap(n1, n2, item_size);
      }
    }
  }
}

int main(void) {
  u64 arr[] = {200, 100, 50, 20, 35, 0, 5, 10, 45, 15};

  ut_print_array(arr, ARRSIZE(arr));

  bubble_sort(arr, ARRSIZE(arr), sizeof(arr[0]), _compare);

  ut_print_array(arr, ARRSIZE(arr));

  return EXIT_SUCCESS;
}
