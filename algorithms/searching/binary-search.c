#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <types.h>
#include <utils.h>

#define NUMELEMENTS 10

bool binary_search(void *arr, size_t arrlen, size_t item_size, void *target,
                   i8 (*compare)(const void *, const void *)) {
  if (arr == NULL || target == NULL || compare == NULL) {
    return false;
  }

  u64 left = 0;
  u64 right = arrlen - 1;
  char *base = (char *)arr;

  while (left <= right) {
    u64 mid = left + (right - left) / 2;
    void *mid_element = (void *)(base + (mid * item_size));

    if (compare(target, mid_element) < 0) {
      right = mid - 1;
    } else if (compare(target, mid_element) > 0) {
      left = mid + 1;
    } else {
      return true;
    }
  }

  return false;
}

int main(void) {
  u64 arr[NUMELEMENTS] = {0};

  for (size_t i = 0; i < NUMELEMENTS; i++) {
    arr[i] = i + 1;
  }

  ut_print_array(arr, NUMELEMENTS);

  u64 target = 9;

  if (binary_search(arr, ARRSIZE(arr), sizeof(arr[0]), &target, ut_compare_u64)) {
    printf("\nFound! (%lu)\n", target);
  }

  return EXIT_SUCCESS;
}
