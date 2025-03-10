#include <stddef.h>
#include <stdlib.h>

#include "ds/dyrray.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {20, 30, 50, 10, 70, 100, 200, 300, 250, 80, 60};

    dyrray dr = {0};

    ut_assert(dyrray_init(&dr, sizeof(u64), DYRRAY_DEFAULT_CAPACITY) == true);

    for (size_t i = 0; i < ARRSIZE(arr); i++) {
        ut_assert(dyrray_push(&dr, &arr[i]) == true);
    }

    ut_assert(dyrray_pop(&dr) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, dr.size - 1), u64 *) == 80);

    ut_assert(dyrray_pop(&dr) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, dr.size - 1), u64 *) == 250);

    ut_assert(dyrray_pop(&dr) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, dr.size - 1), u64 *) == 300);

    ut_assert(dyrray_insert(&dr, &arr[10], dr.size) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, dr.size - 1), u64 *) == 60);

    ut_assert(dyrray_insert(&dr, &arr[9], 3) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, 3), u64 *) == 80);

    ut_assert(dyrray_delete(&dr, dr.size - 1) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, dr.size - 1), u64 *) == 300);

    ut_assert(dyrray_delete(&dr, 3) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, 3), u64 *) == 10);

    ut_assert(dyrray_swap(&dr, 0, 1) == true);
    ut_assert(UT_GETAS(dyrray_get(&dr, 0), u64 *) == 30);
    ut_assert(UT_GETAS(dyrray_get(&dr, 1), u64 *) == 20);

    size_t sz = dr.size;
    for (size_t i = 0; i < sz; i++) {
        ut_assert(dyrray_pop(&dr) == true);
    }

    dyrray_destroy(&dr);

    return EXIT_SUCCESS;
}
