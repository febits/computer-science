#include <stdlib.h>

#include "ds/pqueue.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {50, 30, 40, 10, 60};

    pqueue pq;

    ut_assert(pqueue_init(&pq, sizeof(u64)) == true);
    ut_assert(pq_isempty(&pq) == true);

    ut_assert(pq_enqueue(&pq, &arr[0], ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 50);

    ut_assert(pq_enqueue(&pq, &arr[1], ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 50);

    ut_assert(pq_enqueue(&pq, &arr[2], ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 50);

    ut_assert(pq_enqueue(&pq, &arr[3], ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 50);

    ut_assert(pq_enqueue(&pq, &arr[4], ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 60);

    ut_assert(pq_dequeue(&pq, ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 50);

    ut_assert(pq_dequeue(&pq, ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 40);

    ut_assert(pq_dequeue(&pq, ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 30);

    ut_assert(pq_dequeue(&pq, ut_compare_u64) == true);
    ut_assert(UT_GETAS(pq_front(&pq), u64 *) == 10);

    ut_assert(pq_dequeue(&pq, ut_compare_u64) == true);
    ut_assert(pq_front(&pq) == NULL);

    ut_assert(pq_isempty(&pq) == true);

    pqueue_destroy(&pq);

    return EXIT_SUCCESS;
}
