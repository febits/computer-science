#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds/graphm.h"

#define GRAPHNULL (graphm){NULL, 0}

void graphm_destroy(graphm *g) {
    if (g == NULL) {
        return;
    }

    for (size_t i = 0; i < g->vertices; i++) {
        free(g->adjmatrix[i]);
    }

    free(g->adjmatrix);
}

bool graphm_init(graphm *g, size_t vertices_num) {
    if (g == NULL) {
        return false;
    }

    *g = (graphm){calloc(vertices_num, sizeof(bool *)), vertices_num};
    if (g->adjmatrix == NULL) {
        *g = GRAPHNULL;
        return false;
    }

    for (size_t i = 0; i < g->vertices; i++) {
        g->adjmatrix[i] = calloc(g->vertices, sizeof(bool));
        if (g->adjmatrix[i] == NULL) {
            graphm_destroy(g);
            *g = GRAPHNULL;
            return false;
        }
    }

    return true;
}

bool graphm_add_edge(graphm *g, size_t from, size_t to) {
    if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
        to >= g->vertices) {
        return false;
    }

    g->adjmatrix[from][to] = true;
    return true;
}

bool graphm_is_edge(graphm *g, size_t from, size_t to) {
    if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
        to >= g->vertices || g->adjmatrix[from][to] == false) {
        return false;
    }

    return true;
}

bool graphm_delete_edge(graphm *g, size_t from, size_t to) {
    if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
        to >= g->vertices) {
        return false;
    }

    g->adjmatrix[from][to] = false;
    return true;
}
