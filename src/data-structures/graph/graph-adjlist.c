#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

typedef struct adjlist_node {
  struct adjlist_node *next;
  u64 vertex;
} adjlist_node;

typedef struct {
  u64 vertices;
  adjlist_node **adjlist;
} graph;

graph *graph_init(u64 vertices) {
  graph *g = malloc(sizeof(graph));
  if (g == NULL) return NULL;

  g->vertices = vertices;
  g->adjlist = calloc(g->vertices, sizeof(adjlist_node *));
  if (g->adjlist == NULL) {
    free(g);
    return NULL;
  }

  return g;
}

static adjlist_node *create_node(u64 vertex) {
  adjlist_node *node = malloc(sizeof(adjlist_node));
  if (node == NULL) return NULL;

  node->vertex = vertex;
  node->next = NULL;

  return node;
}

bool add_edge(graph *g, u64 from, u64 to) {
  if (g == NULL || g->adjlist == NULL || from >= g->vertices ||
      to >= g->vertices) {
    return false;
  }

  adjlist_node *node = create_node(to);
  if (node == NULL) return NULL;
  node->next = g->adjlist[from];
  g->adjlist[from] = node;

  // node = create_node(from);
  // if (node == NULL) return NULL;
  // node->next = g->adjlist[to];
  // g->adjlist[to] = node;

  return true;
}

bool is_edge(graph *g, u64 from, u64 to) {
  if (g == NULL || g->adjlist == NULL || from >= g->vertices ||
      to >= g->vertices) {
    return false;
  }

  for (adjlist_node *curr = g->adjlist[from]; curr; curr = curr->next) {
    if (curr->vertex == to) {
      return true;
    }
  }

  return false;
}

void display(graph *g) {
  if (g == NULL) {
    return;
  }

  printf("\n");
  for (size_t i = 0; i < g->vertices; i++) {
    printf(" %lu | ", i);
    adjlist_node *curr = g->adjlist[i];
    for (; curr; curr = curr->next) {
      printf("%lu%s", curr->vertex, curr->next ? " -> " : "");
    }
    printf("\n");
  }
  printf("\n");
}

void destroy(graph *g) {
  if (g == NULL) {
    return;
  }
  
  for (size_t i = 0; i < g->vertices; i++) {
    adjlist_node *tmp = NULL;
    adjlist_node *curr = g->adjlist[i];
    while (curr) {
      tmp = curr;
      curr = curr->next;
      free(tmp);
    }
  }

  free(g->adjlist);
  free(g);
}

bool gendotfile(graph *g, const char *filename) {
  FILE *f = fopen(filename, "w");
  if (f == NULL) return NULL;

  fprintf(f, "strict graph{\n");
  fprintf(f, "\tnode [shape=circle];\n");
  for (size_t i = 0; i < g->vertices; i++) {
    for (adjlist_node *curr = g->adjlist[i]; curr; curr = curr->next) {
      fprintf(f, "\t%lu -- %lu;\n", i, curr->vertex);
    }
  }
  fprintf(f, "}\n");

  fclose(f);
  return true;
}
