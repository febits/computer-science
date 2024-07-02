#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <types.h>
#include <utils.h>

#define NUMELEMENTS 100000

bool binary_search(u64 *arr, size_t arrlen, u64 target) {
  if (arr == NULL || target > arrlen) {
    return false;
  }

  u64 left = 0;
  u64 right = arrlen - 1;

  while (left <= right) {
    u64 mid = left + (right - left) / 2;

    if (target < arr[mid]) {
      right = mid - 1;
    } else if (target > arr[mid]) {
      left = mid + 1;
    } else {
      return true;
    }
  }
  
  return false;
}

int main(void) {
  u64 *arr = malloc(sizeof(u64) * NUMELEMENTS);

  if (arr == NULL) {
    error("allocation error\n");
  }

  for (size_t i = 0; i < NUMELEMENTS; i++) {
    arr[i] = i + 1;
  }

  ut_print_array(arr, NUMELEMENTS);

  if (binary_search(arr, NUMELEMENTS, 56569)) {
    printf("\nFound!\n");
  }

  return EXIT_SUCCESS;
}
