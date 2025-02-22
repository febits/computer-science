#include <ctype.h>
#include <stdbool.h>

#include "algorithms/stoi.h"

int stoi(const char *s) {
    bool neg = false;
    int r = 0;

    while (*s == ' ') {
        s++;
    }

    switch (*s) {
        case '-': neg = true;
        case '+': s++;
    }

    while (isdigit(*s)) {
        r = (10 * r) + (*s++ - '0');
    }

    return neg ? -r : r;
}
