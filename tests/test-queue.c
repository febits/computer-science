#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "queue.h"

int main(void) {
    u64 arr[] = {50, 100, 200, 40};

    ut_print_array(arr, ARRSIZE(arr));

    queue q = queue_init();

    ut_assert(q.size == 0);
    ut_assert(q_dequeue(&q) == false);
    ut_assert(q_front(&q) == NULL);
    ut_assert(q_isempty(&q) == true);

    ut_assert(q_enqueue(&q, &arr[0]) == true);
    ut_assert(q.size == 1);
    ut_assert(UT_GETAS(q.rear->data, u64 *) == 50);

    ut_assert(q_enqueue(&q, &arr[1]) == true);
    ut_assert(q.size == 2);
    ut_assert(UT_GETAS(q.rear->data, u64 *) == 100);

    ut_assert(q_enqueue(&q, &arr[2]) == true);
    ut_assert(q.size == 3);
    ut_assert(UT_GETAS(q.rear->data, u64 *) == 200);

    ut_assert(q_enqueue(&q, &arr[3]) == true);
    ut_assert(q.size == 4);
    ut_assert(UT_GETAS(q.rear->data, u64 *) == 40);

    ut_assert(q_dequeue(&q) == true);
    ut_assert(q.size == 3);
    ut_assert(UT_GETAS(q.front->data, u64 *) == 100);

    ut_assert(q_dequeue(&q) == true);
    ut_assert(q.size == 2);
    ut_assert(UT_GETAS(q.front->data, u64 *) == 200);

    ut_assert(q_front(&q) != NULL);
    ut_assert(UT_GETAS(q_front(&q)->data, u64 *) == 200);

    ut_assert(q_isempty(&q) == false);

    q_destroy(&q);

    ut_assert(q_isempty(&q) == true);
    ut_assert(q.size == 0);
    ut_assert(q.front == NULL);
    ut_assert(q.rear == NULL);

    return EXIT_SUCCESS;
}
