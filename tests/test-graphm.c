#include <stdlib.h>

#include "ds/graphm.h"
#include "utils.h"

int main(void) {
    graphm g = graphm_init(4);

    ut_assert(g.adjmatrix != NULL);

    ut_assert(graphm_add_edge(&g, 0, 1) == true);
    ut_assert(graphm_add_edge(&g, 0, 2) == true);
    ut_assert(graphm_add_edge(&g, 1, 3) == true);

    ut_assert(graphm_is_edge(&g, 0, 1) == true);
    ut_assert(graphm_is_edge(&g, 0, 2) == true);
    ut_assert(graphm_is_edge(&g, 1, 3) == true);

    ut_assert(graphm_add_edge(&g, 5, 5) == false);
    ut_assert(graphm_is_edge(&g, 5, 5) == false);

    ut_assert(graphm_delete_edge(&g, 0, 1) == true);
    ut_assert(graphm_is_edge(&g, 0, 1) == false);
    ut_assert(graphm_delete_edge(&g, 0, 2) == true);
    ut_assert(graphm_is_edge(&g, 0, 2) == false);
    ut_assert(graphm_delete_edge(&g, 1, 3) == true);
    ut_assert(graphm_is_edge(&g, 1, 3) == false);

    for (size_t i = 0; i < g.vertices; i++) {
        for (size_t j = 0; j < g.vertices; j++) {
            ut_assert(graphm_is_edge(&g, i, j) == false);
        }
    }

    graphm_destroy(&g);

    return EXIT_SUCCESS;
}
