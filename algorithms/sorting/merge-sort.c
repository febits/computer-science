#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"

typedef i8(compare)(const void *, const void *);

static void _merge(void *arr, u64 l, u64 m, u64 r, size_t item_size,
                   compare *cmp) {
  u64 n1 = m - l + 1;
  u64 n2 = r - m;

  char *L = malloc(item_size * n1);
  char *R = malloc(item_size * n2);
  char *base = (char *)arr;

  for (u64 i = 0; i < n1; i++) {
    memcpy(L + (i * item_size), base + ((l + i) * item_size), item_size);
  }
  for (u64 j = 0; j < n2; j++) {
    memcpy(R + (j * item_size), base + ((m + j + 1) * item_size), item_size);
  }

  u64 i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (cmp(L + (i * item_size), R + (j * item_size)) <= 0) {
      memcpy(base + (k * item_size), L + (i * item_size), item_size);
      i++;
    } else {
      memcpy(base + (k * item_size), R + (j * item_size), item_size);
      j++;
    }
    k++;
  }

  while (i < n1) {
    memcpy(base + (k * item_size), L + (i * item_size), item_size);
    i++;
    k++;
  }

  while (j < n2) {
    memcpy(base + (k * item_size), R + (j * item_size), item_size);
    j++;
    k++;
  }

  free(L);
  free(R);
}

static void _merge_sort(void *arr, u64 left, u64 right, size_t item_size,
                        compare *cmp) {
  if (left < right) {
    u64 mid = left + (right - left) / 2;

    _merge_sort(arr, left, mid, item_size, cmp);
    _merge_sort(arr, mid + 1, right, item_size, cmp);
    _merge(arr, left, mid, right, item_size, cmp);
  }
}

void merge_sort(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
  if (arr == NULL || cmp == NULL) {
    return;
  }

  _merge_sort(arr, 0, arrlen - 1, item_size, cmp);
}

int main(void) {
  u64 arr[] = {
      200, 1, 100, 50, 20, 35, 0, 5, 10, 45, 15,
  };

  ut_print_array(arr, ARRSIZE(arr));
  merge_sort(arr, ARRSIZE(arr), sizeof(arr[0]), ut_compare_u64);
  ut_print_array(arr, ARRSIZE(arr));

  return EXIT_SUCCESS;
}
