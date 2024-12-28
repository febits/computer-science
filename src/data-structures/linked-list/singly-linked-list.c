#include <stdio.h>
#include <stdlib.h>

#include "singlyll.h"
#include "types.h"

singly_ll *ll_init(void) {
  singly_ll *ll = malloc(sizeof(singly_ll));
  if (ll == NULL) {
    return NULL;
  }

  ll->head = NULL;
  ll->size = 0;

  return ll;
}

static ll_node *_insert_at_head(singly_ll *ll, ll_node *node) {
  node->next = ll->head;
  ll->head = node;

  ll->size++;
  return node;
}

static ll_node *_insert_at_tail(singly_ll *ll, ll_node *node) {
  ll_node *curr = ll->head;
  for (; curr->next; curr = curr->next) {
    ;
  }

  curr->next = node;

  ll->size++;
  return node;
}

static ll_node *_insert_at_pos(singly_ll *ll, ll_node *node, u64 pos) {
  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (u64 i = 0; i < pos; i++, prev = curr, curr = curr->next) {
    ;
  }

  node->next = curr;
  prev->next = node;

  ll->size++;
  return node;
}

ll_node *ll_insert(singly_ll *ll, void *data, op_type type, i64 pos) {
  ll_node *node = malloc(sizeof(ll_node));

  if (ll == NULL || node == NULL || pos >= (i64)ll->size) {
    return NULL;
  }

  node->data = data;
  node->next = NULL;

  if (type == AT_HEAD && pos <= NOINDEX) {
    return _insert_at_head(ll, node);
  } else if (type == AT_TAIL && pos <= NOINDEX) {
    if (ll->size == 0) {
      return _insert_at_head(ll, node);
    }

    return _insert_at_tail(ll, node);
  } else if (type == AT_POSITION && pos > NOINDEX) {
    if (pos == 0 || pos == (i64)ll->size - 1) {
      switch (pos) {
        case 0: return _insert_at_head(ll, node); break;
        default: return _insert_at_tail(ll, node);
      }
    }

    return _insert_at_pos(ll, node, pos);
  }

  return NULL;
}

static ll_node *_delete_at_head(singly_ll *ll) {
  ll_node *tmp = ll->head;
  ll->head = ll->head->next;

  ll->size--;
  return tmp;
}

static ll_node *_delete_at_tail(singly_ll *ll) {
  ll_node *tmp = NULL;

  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (; curr->next; prev = curr, curr = curr->next) {
    ;
  }

  tmp = curr;
  prev->next = NULL;

  ll->size--;
  return tmp;
}

static ll_node *_delete_at_position(singly_ll *ll, u64 pos) {
  ll_node *tmp = NULL;

  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (u64 i = 0; i < pos; i++, prev = curr, curr = curr->next) {
    ;
  }

  tmp = curr;
  prev->next = curr->next;

  ll->size--;
  return tmp;
}

static ll_node *_delete_by_value(singly_ll *ll, void *data, compare *cmp) {
  ll_node *tmp = NULL;

  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (; curr; prev = curr, curr = curr->next) {
    if (cmp(curr->data, data) == 0) {
      tmp = curr;
      prev->next = curr->next;
      break;
    }
  }

  ll->size--;
  return tmp;
}

ll_node *ll_delete(singly_ll *ll, void *data, op_type type, i64 pos,
                   compare *cmp) {
  if (ll == NULL || ll->head == NULL || pos >= (i64)ll->size) {
    return NULL;
  }

  if (type == AT_HEAD && pos <= NOINDEX) {
    return _delete_at_head(ll);
  } else if (type == AT_TAIL && pos <= NOINDEX) {
    if (ll->size == 1) {
      return _delete_at_head(ll);
    }

    return _delete_at_tail(ll);
  } else if (type == BY_VALUE && pos <= NOINDEX && cmp) {
    if (cmp(ll->head->data, data) == 0) {
      return _delete_at_head(ll);
    }

    return data != NULL ? _delete_by_value(ll, data, cmp) : NULL;
  } else if (type == AT_POSITION && pos > NOINDEX) {
    if (pos == 0 || pos == (i64)ll->size - 1) {
      switch (pos) {
        case 0: return _delete_at_head(ll); break;
        default: return _delete_at_tail(ll);
      }
    }

    return _delete_at_position(ll, pos);
  }

  return NULL;
}

ll_node *ll_search(singly_ll *ll, void *data, compare *cmp) {
  if (ll == NULL || cmp == NULL) {
    return NULL;
  }

  for (ll_node *curr = ll->head; curr; curr = curr->next) {
    if (cmp(curr->data, data) == 0) {
      return curr;
    }
  }

  return NULL;
}

ll_node *ll_get(singly_ll *ll, u64 pos) {
  if (ll == NULL || pos >= ll->size) {
    return NULL;
  }

  ll_node *curr = ll->head;
  for (u64 i = 0; i < pos; i++, curr = curr->next) {
    ;
  }

  return curr;
}

void ll_destroy(singly_ll *ll) {
  if (ll == NULL) {
    return;
  }

  size_t sz = ll->size;
  for (size_t i = 0; i < sz; i++) {
    free(ll_delete(ll, NULL, AT_HEAD, -1, NULL));
  }

  free(ll);
}