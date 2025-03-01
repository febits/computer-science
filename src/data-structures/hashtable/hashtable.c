#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "ds/hash.h"

#define HASHTNULL                                                              \
    (hashtable) { NULL, 0, NULL }

bool hash_init(hashtable *h, hashfunc hashf, size_t nbuckets) {
    if (h == NULL) {
        return false;
    }

    if (hashf == NULL) {
        *h = HASHTNULL;
        return false;
    }

    *h = (hashtable){NULL, nbuckets, hashf};

    h->buckets = calloc(nbuckets, sizeof(hentry *));

    if (h->buckets == NULL) {
        *h = HASHTNULL;
        return false;
    }

    return true;
}

static hentry *_create_node(const char *key, void *data) {
    if (strlen(key) > KEYLEN) {
        return NULL;
    }

    hentry *e = malloc(sizeof(hentry));

    if (e == NULL) {
        return NULL;
    }

    e->key = malloc(sizeof(char) * (KEYLEN + 1));

    if (e->key == NULL) {
        free(e);
        return NULL;
    }

    strncpy(e->key, key, KEYLEN);

    e->data = data;
    e->next = NULL;

    return e;
}

bool hash_contains(hashtable *h, const char *key) {
    if (h == NULL || key == NULL) {
        return false;
    }

    uint64_t index = h->hashf(key) % h->capacity;
    hentry *tentry = h->buckets[index];

    while (tentry != NULL) {
        if (strncmp(tentry->key, key, KEYLEN) == 0) {
            return true;
        }

        tentry = tentry->next;
    }

    return false;
}

bool hash_insert(hashtable *h, const char *key, void *data) {
    if (h == NULL || key == NULL || hash_contains(h, key) == true) {
        return false;
    }

    uint64_t index = h->hashf(key) % h->capacity;
    hentry *e = _create_node(key, data);

    if (e == NULL) {
        return false;
    }

    e->next = h->buckets[index];
    h->buckets[index] = e;

    return true;
}

hentry *hash_get(hashtable *h, const char *key) {
    if (h == NULL || key == NULL) {
        return NULL; 
    }

    uint64_t index = h->hashf(key) % h->capacity;
    hentry *tentry = h->buckets[index];

    while (tentry != NULL) {
        if (strncmp(tentry->key, key, KEYLEN) == 0) {
            return tentry;
        }

        tentry = tentry->next;
    }

    return NULL;
}

static void _free_hentry(hentry *e) {
    if (e == NULL) {
        return;
    }

    free(e->key);
    free(e);
}

bool hash_delete(hashtable *h, const char *key) {
    if (h == NULL || key == NULL || hash_contains(h, key) == false) {
        return false;
    }

    uint64_t index = h->hashf(key) % h->capacity;
    hentry *tentry = h->buckets[index];

    if (strncmp(tentry->key, key, KEYLEN) == 0) {
        h->buckets[index] = tentry->next;
        _free_hentry(tentry);
    } else {
        while (tentry != NULL) {
            if (strncmp(tentry->next->key, key, KEYLEN) == 0) {
                hentry *fentry = tentry->next;
                tentry->next = fentry->next;
                _free_hentry(fentry);
                break;
            }

            tentry = tentry->next;
        }
    }

    return true;
}

void hash_destroy(hashtable *h) {
    if (h == NULL) {
        return;
    }

    for (size_t i = 0; i < h->capacity; i++) {
        hentry *tentry = h->buckets[i];

        while (tentry != NULL) {
            hentry *tmp = tentry;
            tentry = tmp->next;
            _free_hentry(tmp);
        }
    }
    
    free(h->buckets);
}
