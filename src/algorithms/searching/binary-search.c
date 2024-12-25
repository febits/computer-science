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
