#include <stdlib.h>

#include "stack.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {50, 60, 10, 200, 100};

    ut_print_array(arr, ARRSIZE(arr));

    stack s = stack_init();

    ut_assert(s.size == 0);
    ut_assert(stack_pop(&s) == false);
    ut_assert(stack_peek(&s) == NULL);
    ut_assert(stack_isempty(&s) == true);

    ut_assert(stack_push(&s, &arr[0]) == true);
    ut_assert(s.size == 1);
    ut_assert(UT_GETAS(s.top->data, u64 *) == 50);

    ut_assert(stack_push(&s, &arr[1]) == true);
    ut_assert(s.size == 2);
    ut_assert(UT_GETAS(s.top->data, u64 *) == 60);

    ut_assert(stack_push(&s, &arr[2]) == true);
    ut_assert(s.size == 3);
    ut_assert(UT_GETAS(s.top->data, u64 *) == 10);

    ut_assert(stack_push(&s, &arr[3]) == true);
    ut_assert(s.size == 4);
    ut_assert(UT_GETAS(s.top->data, u64 *) == 200);

    ut_assert(stack_push(&s, &arr[4]) == true);
    ut_assert(s.size == 5);
    ut_assert(UT_GETAS(s.top->data, u64 *) == 100);

    ut_assert(stack_pop(&s) == true);
    ut_assert(s.size == 4);
    ut_assert(UT_GETAS(s.top->data, u64 *) == 200);

    ut_assert(stack_pop(&s) == true);
    ut_assert(s.size == 3);
    ut_assert(UT_GETAS(s.top->data, u64 *) == 10);

    ut_assert(stack_peek(&s) != NULL);
    ut_assert(UT_GETAS(stack_peek(&s)->data, u64 *) == 10);

    ut_assert(stack_isempty(&s) == false);

    stack_destroy(&s);

    ut_assert(stack_isempty(&s) == true);
    ut_assert(s.size == 0);
    ut_assert(s.top == NULL);

    return EXIT_SUCCESS;
}
