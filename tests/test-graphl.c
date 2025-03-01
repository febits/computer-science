#include <stdlib.h>

#include "ds/graphl.h"
#include "utils.h"

int main(void) {
    graphl g;

    ut_assert(graphl_init(&g, 4) == true);
    ut_assert(g.adjlist != NULL);

    ut_assert(graphl_add_edge(&g, 0, 1) == true);
    ut_assert(graphl_add_edge(&g, 0, 2) == true);
    ut_assert(graphl_add_edge(&g, 1, 3) == true);

    ut_assert(graphl_is_edge(&g, 0, 1) == true);
    ut_assert(graphl_is_edge(&g, 0, 2) == true);
    ut_assert(graphl_is_edge(&g, 1, 3) == true);

    ut_assert(graphl_add_edge(&g, 5, 5) == false);
    ut_assert(graphl_is_edge(&g, 5, 5) == false);

    graphl_destroy(&g);

    return EXIT_SUCCESS;
}
