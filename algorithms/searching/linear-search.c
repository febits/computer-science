#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

#define NUMELEMENTS 10

static i8 _compare(const void *a, const void *b) {
  const u64 _a = *(const u64 *)a;
  const u64 _b = *(const u64 *)b;

  return (_a > _b) - (_a < _b);
}

bool linear_search(void *arr, size_t arrlen, size_t item_size, void *target,
                   i8 (*compare)(const void *, const void *)) {
  if (arr == NULL || target == NULL || compare == NULL) {
    return false;
  }

  char *base = (char *)arr;
  for (size_t i = 0; i < arrlen; i++) {
    if (compare(target, (void *)(base + (i * item_size))) == 0) {
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

  u64 target = 5;

  if (linear_search(arr, ARRSIZE(arr), sizeof(arr[0]), &target, _compare)) {
    printf("\nFound! (%lu)\n", target);
  }

  return EXIT_SUCCESS;
}
