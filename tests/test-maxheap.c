#include <stdlib.h>

#include "ds/maxheap.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {10, 50, 40, 60, 100};
    u64 arr2[] = {20, 30, 50, 70, 120, 150};

    maxheap hp;

    ut_assert(maxheap_init(&hp, sizeof(u64)) == true);
    ut_assert(maxheap_peek(&hp) == NULL);

    ut_assert(maxheap_push(&hp, &arr[0], ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 10);
    ut_assert(hp.size == 1);

    ut_assert(maxheap_push(&hp, &arr[1], ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 50);
    ut_assert(hp.size == 2);

    ut_assert(maxheap_push(&hp, &arr[2], ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 50);
    ut_assert(hp.size == 3);

    ut_assert(maxheap_push(&hp, &arr[3], ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 60);
    ut_assert(hp.size == 4);

    ut_assert(maxheap_push(&hp, &arr[4], ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 100);
    ut_assert(hp.size == 5);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 100);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 60);
    ut_assert(hp.size == 4);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 60);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 50);
    ut_assert(hp.size == 3);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 50);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 40);
    ut_assert(hp.size == 2);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 40);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 10);
    ut_assert(hp.size == 1);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 10);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(maxheap_peek(&hp) == NULL);
    ut_assert(hp.size == 0);

    ut_assert(maxheap_pop(&hp, ut_compare_u64) == false);

    maxheap_destroy(&hp);

    ut_assert(maxheap_init(&hp, sizeof(u64)) == true);
    ut_assert(maxheap_heapify(&hp, arr2, ARRSIZE(arr2), ut_compare_u64) ==
              true);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 150);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 120);
    ut_assert(hp.size == 5);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 120);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 70);
    ut_assert(hp.size == 4);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 70);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 50);
    ut_assert(hp.size == 3);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 50);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 30);
    ut_assert(hp.size == 2);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 30);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 20);
    ut_assert(hp.size == 1);

    ut_assert(UT_GETAS(maxheap_peek(&hp), u64 *) == 20);
    ut_assert(maxheap_pop(&hp, ut_compare_u64) == true);
    ut_assert(maxheap_peek(&hp) == NULL);
    ut_assert(hp.size == 0);

    maxheap_destroy(&hp);

    return EXIT_SUCCESS;
}
