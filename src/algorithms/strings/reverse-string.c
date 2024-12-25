#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"

void reverse_string(char *s) {
  u64 left = 0;
  u64 right = strlen(s) - 1;

  while (left < right) {
    ut_swap(&s[left++], &s[right--], sizeof(char));
  }
}
