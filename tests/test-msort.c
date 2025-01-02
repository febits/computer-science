#include <stdlib.h>

#include "msort.h"
#include "types.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {10, 1000, 200, 100, 0, 20};

    ut_assert(ut_array_sorted(arr, ARRSIZE(arr), sizeof(u64), ut_compare_u64) ==
              false);

    ut_print_array(arr, ARRSIZE(arr));
    merge_sort(arr, ARRSIZE(arr), sizeof(u64), ut_compare_u64);
    ut_print_array(arr, ARRSIZE(arr));

    ut_assert(ut_array_sorted(arr, ARRSIZE(arr), sizeof(u64), ut_compare_u64) ==
              true);

    return EXIT_SUCCESS;
}