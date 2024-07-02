#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "utils.h"

#define NUMELEMENTS 100000

bool linear_search(u64 *arr, size_t arrlen, u64 target) {
  if (arr == NULL || target > arrlen) {
    return false;
  }

  for (size_t i = 0; i < arrlen; i++) {
    if (arr[i] == target) {
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

  if (linear_search(arr, NUMELEMENTS, NUMELEMENTS)) {
    printf("\nFound!\n");
  }

  return EXIT_SUCCESS;
}
