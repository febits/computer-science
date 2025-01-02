#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define OFF "\033[0m"

void ut_assert_print(const char *file, const char *func, int line,
                     const char *expr, ut_assert_print_type type) {
    switch (type) {
        case PASSED:
            fprintf(stdout, GREEN "ASSERT PASSED: " OFF "%s:%d: %s: '%s'\n",
                    file, line, func, expr);
            break;
        case FAILED:
            fprintf(stderr, RED "ASSERT FAILED: " OFF "%s:%d: %s: '%s'\n", file,
                    line, func, expr);
            exit(EXIT_FAILURE);
            break;
    }
}

bool ut_array_sorted(void *arr, size_t arrlen, size_t item_size, compare *cmp) {
    if (arr == NULL || cmp == NULL) {
        return false;
    }

    char *base = arr;
    for (size_t i = 0; i < arrlen - 1; i++) {
        void *n1 = base + (item_size * i);
        void *n2 = base + (item_size * (i + 1));

        if (cmp(n1, n2) > 0) {
            return false;
        }
    }

    return true;
}

i8 ut_compare_u64(const void *a, const void *b) {
    const u64 _a = *(const u64 *)a;
    const u64 _b = *(const u64 *)b;

    return (_a > _b) - (_a < _b);
}

void ut_swap(void *a, void *b, size_t item_size) {
    void *tmp = malloc(item_size);
    memcpy(tmp, a, item_size);
    memcpy(a, b, item_size);
    memcpy(b, tmp, item_size);
    free(tmp);
}

void ut_print_unsupported(void *arr, size_t arrlen) {
    printf("[unsupported type]\n");
}

void ut_print_u64arr(u64 *arr, size_t arrlen) {
    printf("[");

    for (size_t i = 0; i < arrlen; i++) {
        printf("%lu", arr[i]);

        if (i != arrlen - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void ut_print_strarr(char **arr, size_t arrlen) {
    printf("[");

    for (size_t i = 0; i < arrlen; i++) {
        printf("%s", arr[i]);

        if (i != arrlen - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
