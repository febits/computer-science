#include <stdlib.h>

#include "bsearch.h"
#include "types.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {10, 20, 30, 50, 70, 100};

    u64 found = 70;
    u64 not_found = 200;

    ut_print_array(arr, ARRSIZE(arr));

    ut_assert(binary_search(arr, ARRSIZE(arr), sizeof(u64), &found,
                            ut_compare_u64) == true);

    ut_assert(binary_search(arr, ARRSIZE(arr), sizeof(u64), &not_found,
                            ut_compare_u64) == false);

    return EXIT_SUCCESS;
}
