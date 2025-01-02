#include "utils.h"
#include <string.h>

void reverse_string(char *s) {
    size_t left = 0;
    size_t right = strlen(s) - 1;

    while (left < right) {
        char c = s[left];
        s[left] = s[right];
        s[right] = c;

        left++, right--;
    }
}
