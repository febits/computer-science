#include <stdlib.h>

#include "ds/cqueue.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {10, 50, 30, 40, 100};

    cqueue cq;

    ut_assert(cqueue_init(&cq, 5, sizeof(u64)) == true);
    ut_assert(cq_isempty(&cq) == true);

    for (size_t i = 0; i < ARRSIZE(arr); i++) {
        ut_assert(cq_enqueue(&cq, &arr[i]) == true);
        ut_assert(UT_GETAS(cq_rear(&cq), u64 *) == arr[i]);
    }

    ut_assert(cq_isfull(&cq) == true);
    ut_assert(UT_GETAS(cq_front(&cq), u64 *) == 10);

    ut_assert(cq_dequeue(&cq) == true);
    ut_assert(UT_GETAS(cq_front(&cq), u64 *) == 50)

    ut_assert(cq_dequeue(&cq) == true);
    ut_assert(UT_GETAS(cq_front(&cq), u64 *) == 30)

    ut_assert(cq_enqueue(&cq, &arr[0]) == true);
    ut_assert(UT_GETAS(cq_rear(&cq), u64 *) == 10)

    ut_assert(cq_enqueue(&cq, &arr[1]) == true);
    ut_assert(UT_GETAS(cq_rear(&cq), u64 *) == 50);

    ut_assert(cq_isfull(&cq) == true);
    ut_assert(cq_isempty(&cq) == false);

    cqueue_destroy(&cq);

    return EXIT_SUCCESS;
}
