#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

#define NUMELEMENTS 10

bool jump_search(void *arr, size_t arrlen, size_t item_size, void *target,
                 i8 (*cmp)(const void *, const void *)) {
  if (arr == NULL || cmp == NULL || target == NULL) {
    return false;
  }

  char *base = (char *)arr;

  u64 step = sqrt(arrlen);
  u64 curr = 0;
  u64 prev = 0;

  while (curr < arrlen && cmp(base + (curr * item_size), target) < 0) {
    prev = curr;
    curr += step;
    if (curr > arrlen - 1) {
      curr = arrlen;
    }
  }

  for (u64 i = prev; i <= curr; i++) {
    if (cmp(base + (i * item_size), target) == 0) {
      return true;
    }
  }

  return false;
}
