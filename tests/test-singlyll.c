#include <stdio.h>

#include "singlyll.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {10, 50, 30, 40, 60};

    ut_print_array(arr, ARRSIZE(arr));

    singly_ll ll = ll_init();

    ut_assert(ll_insert_at_head(&ll, &arr[0]) == true);
    ut_assert(ll_insert_at_tail(&ll, &arr[1]) == true);

    ut_assert(ll.size == 2);
    ut_assert(UT_GETAS(ll.head->data, u64 *) == 10);
    ut_assert(UT_GETAS(ll.head->next->data, u64 *) == 50);

    ut_assert(ll_insert_at_pos(&ll, &arr[2], 1) == true);
    ut_assert(ll.size == 3);
    ut_assert(UT_GETAS(ll.head->next->data, u64 *) == 30);
    ut_assert(UT_GETAS(ll.head->next->next->data, u64 *) == 50);

    ut_assert(ll_insert_at_pos(&ll, &arr[3], 3) == false);
    ut_assert(ll_insert_at_pos(&ll, &arr[3], 4) == false);

    ut_assert(ll_insert_at_pos(&ll, &arr[3], 1) == true);
    ut_assert(ll.size == 4);
    ut_assert(UT_GETAS(ll.head->next->data, u64 *) == 40);

    ut_assert(ll_insert_at_pos(&ll, &arr[4], 3) == true);
    ut_assert(ll.size == 5);
    ut_assert(UT_GETAS(ll.head->next->next->next->data, u64 *) == 60);

    ut_assert(ll_delete_at_head(&ll) == true);
    ut_assert(ll.size == 4);
    ut_assert(UT_GETAS(ll.head->data, u64 *) == 40);

    ut_assert(ll_delete_at_tail(&ll) == true);
    ut_assert(ll.size == 3);
    ut_assert(UT_GETAS(ll.head->next->next->data, u64 *) == 60);

    ut_assert(ll_delete_at_pos(&ll, 1) == true);
    ut_assert(ll.size == 2);
    ut_assert(UT_GETAS(ll.head->next->data, u64 *) == 60);

    ut_assert(ll_delete_by_value(&ll, &arr[3], ut_compare_u64) == true);
    ut_assert(ll.size == 1);
    ut_assert(UT_GETAS(ll.head->data, u64 *) == 60);

    ut_assert(ll_insert_at_tail(&ll, &arr[0]) == true);
    ut_assert(ll.size == 2);
    ut_assert(UT_GETAS(ll.head->data, u64 *) == 60);

    ut_assert(ll_search(&ll, &arr[0], ut_compare_u64) != NULL);
    ut_assert(ll_search(&ll, &arr[4], ut_compare_u64) != NULL);
    ut_assert(ll_search(&ll, &arr[3], ut_compare_u64) == NULL);

    ut_assert(ll_get(&ll, 2) == NULL);
    ut_assert(ll_get(&ll, 0) != NULL);
    ut_assert(ll_get(&ll, 1) != NULL);

    ut_assert(ll_delete_by_value(&ll, &arr[0], ut_compare_u64) == true);
    ut_assert(ll.size == 1);
    ut_assert(UT_GETAS(ll.head->data, u64 *) == 60);
    ut_assert(ll.head->next == NULL);

    ut_assert(ll_delete_at_tail(&ll) == true);
    ut_assert(ll.size == 0);

    ut_assert(ll_isempty(&ll) == true);
    ut_assert(ll.head == NULL);

    ll_destroy(&ll);

    return 0;
}
