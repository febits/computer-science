#include <stdlib.h>

#include "algorithms/jsearch.h"
#include "types.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {30, 50, 100, 200, 40};

    u64 found = 100;
    u64 not_found = 300;

    ut_print_array(arr, ARRSIZE(arr));

    ut_assert(jump_search(arr, ARRSIZE(arr), sizeof(u64), &found,
                          ut_compare_u64) == true);

    ut_assert(jump_search(arr, ARRSIZE(arr), sizeof(u64), &not_found,
                          ut_compare_u64) == false);

    return EXIT_SUCCESS;
}
