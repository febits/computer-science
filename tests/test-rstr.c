#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rstr.h"
#include "utils.h"

int main(void) {
    char str1[] = "kernel";
    reverse_string(str1);
    ut_assert(strncmp(str1, "lenrek", 6) == 0);

    char str2[] = "ana";
    reverse_string(str2);
    ut_assert(strncmp(str2, "ana", 3) == 0);

    char str3[] = "linux";
    reverse_string(str3);
    ut_assert(strncmp(str3, "xunil", 6) == 0);

    char str4[] = "c++";
    reverse_string(str4);
    ut_assert(strncmp(str4, "++c", 3) == 0);

    char str5[] = "rust";
    reverse_string(str5);
    ut_assert(strncmp(str5, "tsur", 4) == 0);

    return EXIT_SUCCESS;
}
