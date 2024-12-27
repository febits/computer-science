#ifndef SINGLYLL_H
#define SINGLYLL_H

#include <stddef.h>
#include "types.h"

#define NOINDEX (-1)

typedef i8(compare)(const void *, const void *);
typedef enum { AT_HEAD, AT_TAIL, AT_POSITION, BY_VALUE } op_type;

typedef struct ll_node {
  struct ll_node *next;
  void *data;
} ll_node;

typedef struct {
  ll_node *head;
  size_t size;
} singly_ll;

singly_ll *ll_init(void);

ll_node *ll_insert(singly_ll *ll, void *data, op_type type, i64 pos);
ll_node *ll_delete(singly_ll *ll, void *data, op_type type, i64 pos, compare *cmp);
ll_node *ll_search(singly_ll *ll, void *data, compare *cmp);
ll_node *ll_get(singly_ll *ll, u64 pos);

void ll_destroy(singly_ll *ll);

#endif
