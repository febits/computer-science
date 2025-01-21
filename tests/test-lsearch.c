#include <stdlib.h>

#include "algorithms/lsearch.h"
#include "types.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {10, 20, 50, 200, 100};

    u64 found = 100;
    u64 not_found = 30;

    ut_print_array(arr, ARRSIZE(arr));

    ut_assert(linear_search(arr, ARRSIZE(arr), sizeof(u64), &found,
                            ut_compare_u64) == true);

    ut_assert(linear_search(arr, ARRSIZE(arr), sizeof(u64), &not_found,
                            ut_compare_u64) == false);

    return EXIT_SUCCESS;
}
