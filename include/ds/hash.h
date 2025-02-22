#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define KEYLEN 128

typedef uint64_t (*hashfunc)(const char *s);

typedef struct hentry {
    struct hentry *next;

    char *key;
    void *data;
} hentry;

typedef struct {
    hentry **buckets;
    size_t capacity;
    hashfunc hashf;
} hashtable;

hashtable hash_init(hashfunc hashf, size_t nbuckets);

bool hash_insert(hashtable *h, const char *key, void *data);
bool hash_delete(hashtable *h, const char *key);
bool hash_contains(hashtable *h, const char *key);
hentry *hash_get(hashtable *h, const char *key);

void hash_destroy(hashtable *h);

#endif
