#include <stdlib.h>

#include "algorithms/qsort.h"
#include "types.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {100, 200, 20, 0, 10};

    ut_assert(ut_array_sorted(arr, ARRSIZE(arr), sizeof(u64), ut_compare_u64) ==
              false);

    ut_print_array(arr, ARRSIZE(arr));
    quick_sort(arr, ARRSIZE(arr), sizeof(u64), ut_compare_u64);
    ut_print_array(arr, ARRSIZE(arr));

    ut_assert(ut_array_sorted(arr, ARRSIZE(arr), sizeof(u64), ut_compare_u64) ==
              true);

    return EXIT_SUCCESS;
}
