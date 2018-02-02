/*
 * File name: sht.c
 *
 * Copyright(C) 2007-2016, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#include <a10_hash.h>
//#include <sto_types.h>

#include "sht.h"

#define TRUE 1
#define FALSE 0

/**
 * (S)imple (H)ash(i)ng (T)able
 */
sht_bucket_t *sht_bucket_get(sht_t *t, u64 hash)
{
    return &t->buckets[hash % t->num_buckets];
}

void *sht_mem_alloc(unsigned int bytes)
{
    g_sht.mem_alloc++;
    return malloc(bytes);
}

void sht_mem_free(void *ptr)
{
    if (ptr) {
        g_sht.mem_free++;
        free(ptr);
    }
}

sht_t *sht_alloc(u32 num_buckets)
{
    sht_t *t = NULL;
    sht_bucket_t *buckets = NULL;
    unsigned int mem_size;

    t = sht_mem_alloc(sizeof(*t));
    if (!t) {
        goto err;
    }

    mem_size = sizeof(sht_bucket_t) * num_buckets;
    buckets = sht_mem_alloc(mem_size);
    if (!buckets) {
        goto err;
    }

    memset(t, 0, sizeof(*t));
    memset(buckets, 0, mem_size);

    t->num_buckets = num_buckets;
    t->buckets = buckets;

    return t;
err:
    if (t) {
        sht_mem_free(t);
    }
    if (buckets) {
        sht_mem_free(buckets);
    }
    return NULL;
}

void sht_bucket_free(sht_bucket_t *b)
{
    unsigned int i;

    if (!b || !b->entries) {
        return;
    }

    for (i = 0; i < b->next_entry; i++) {
        sht_entry_t *e;

        e = &b->entries[i];
        if (e->key) {
            sht_mem_free((void *)e->key);
            e->key = NULL;
        }
    }

    sht_mem_free(b->entries);
}

void sht_bucket_reset(sht_bucket_t *b)
{
    unsigned int i;

    if (!b || !b->entries) {
        return;
    }

    for (i = 0; i < b->next_entry; i++) {
        sht_entry_t *e;

        e = &b->entries[i];
        if (e->key) {
            sht_mem_free((void *)e->key);
            e->key = NULL;
        }
    }
    b->next_entry = 0;
}

void sht_free(sht_t *t)
{
    unsigned int i;

    if (!t) {
        return;
    }

    for (i = 0; i < t->num_buckets; i++) {
        sht_bucket_free(sht_bucket_get(t, i));
    }

    sht_mem_free(t->buckets);
    sht_mem_free(t);
}

/* careful with this, it's not threadsafe */
void sht_reset(sht_t *t)
{
    unsigned int i;

    for (i = 0; i < t->num_buckets; i++) {
        sht_bucket_reset(sht_bucket_get(t, i));
    }
}

unsigned int sht_num_entries(const sht_t *t)
{
    return t->num_entries;
}

int sht_bucket_resize(sht_bucket_t *b, unsigned int new_size)
{
    sht_entry_t *new_entries;
    sht_entry_t *old_entries;

    new_entries = sht_mem_alloc(new_size * sizeof(sht_entry_t));
    if (!new_entries) {
        return -1;
    }

    memset(new_entries, 0, new_size * sizeof(new_entries[0]));

    old_entries = b->entries;
    if (old_entries) {
        if (new_size > b->max_entries) {
            memcpy(new_entries, old_entries, sizeof(sht_entry_t) * b->max_entries);
        } else {
            memcpy(new_entries, old_entries, sizeof(sht_entry_t) * new_size);
        }
    }

    b->entries = new_entries;
    b->max_entries = new_size;

    if (old_entries) {
        sht_mem_free(old_entries);
    }

    return 0;
}

SHT_INSERT_RET sht_bucket_insert(sht_t *t, sht_bucket_t *b, const void *key, unsigned int key_len, void *value, sht_match_f key_match)
{
    u32 new_size = 0;
    sht_entry_t *e;
    void *key_copy;

    if (b->entries) {
        unsigned int i;

        for (i = 0; i < b->next_entry; i++) {
            e = &b->entries[i];
            if (key_match(key, e->key)) {
                return SHT_INSERT_FOUND;
            }
        }
    }

    if (!b->entries) {
        new_size = SHT_BUCKET_SIZE_DEFAULT;
    } else if (b->next_entry >= b->max_entries) {
        new_size = b->max_entries * 3 / 2;
    }

    if (new_size > 0) {
        if (sht_bucket_resize(b, new_size) < 0) {
            return SHT_INSERT_OOM;
        }
    }

    key_copy = sht_mem_alloc(key_len);
    if (!key_copy) {
        return SHT_INSERT_OOM;
    }
    memcpy(key_copy, key, key_len);

    e = &b->entries[b->next_entry];
    e->key = key_copy;
    e->value = value;

    b->next_entry++;

    t->num_entries++;

    return SHT_INSERT_SUCCESS;
}

SHT_INSERT_RET sht_insert_generic(sht_t *t, const void *key, unsigned int key_len, void *value, u64 key_hash, sht_match_f key_match)
{
    return sht_bucket_insert(t, sht_bucket_get(t, key_hash), key, key_len, value, key_match);
}

void *sht_find_generic(sht_t *t, const void *search_key, u64 key_hash, sht_match_f key_match)
{
    sht_bucket_t *b;
    unsigned int i;

    b = sht_bucket_get(t, key_hash);
    for (i = 0; i < b->next_entry; i++) {
        sht_entry_t *e;

        e = &b->entries[i];
        if (key_match(search_key, e->key)) {
            return (void *)e->value;
        }
    }

    return NULL;
}

void *sht_remove_generic(sht_t *t, const void *search_key, u64 key_hash, sht_match_f key_match)
{
    sht_bucket_t *b;
    unsigned int i;

    b = sht_bucket_get(t, key_hash);
    for (i = 0; i < b->next_entry; i++) {
        sht_entry_t *e;

        e = &b->entries[i];
        if (key_match(search_key, e->key)) {
            void *ret;
            u32 entries_after;

            ret = e->value;
            entries_after = b->next_entry - i - 1;

            if (e->key) {
                sht_mem_free((void *)e->key);
            }
            e->value = NULL;
            b->next_entry--;
            t->num_entries--;

            if (entries_after > 0) {
                /* shrink bucket */
                memmove(&b->entries[i], &b->entries[i + 1], entries_after * sizeof(b->entries[i]));
                if ((b->next_entry > SHT_BUCKET_SIZE_DEFAULT) &&
                    (b->next_entry <= b->max_entries / 4)) {
                    sht_bucket_resize(b, b->max_entries / 4);
                }
            }

            return ret;
        }
    }

    return NULL;
}

int sht_match_str(const void *search_key, const void *entry_key)
{
    return (strcmp(search_key, entry_key) == 0);
}

SHT_INSERT_RET sht_insert_with_str(sht_t *t, const char *key, void *value)
{
    unsigned int key_len;

    /* +1 for the NULL terminator */
    key_len = strlen(key) + 1;
    return sht_insert_generic(t, key, key_len, value, murmurhash3_64(key, key_len), sht_match_str);
}

void *sht_find_with_str(sht_t *t, const char *key)
{
    unsigned int key_len;

    /* +1 for the NULL terminator */
    key_len = strlen(key) + 1;
    return sht_find_generic(t, key, murmurhash3_64(key, key_len), sht_match_str);
}

void *sht_remove_with_str(sht_t *t, const char *key)
{
    unsigned int key_len;

    /* +1 for the NULL terminator */
    key_len = strlen(key) + 1;
    return sht_remove_generic(t, key, murmurhash3_64(key, key_len), sht_match_str);
}

int sht_match_u32(const void *search_key, const void *entry_key)
{
    return (*(const u32 *)search_key == *(const u32 *)entry_key);
}

SHT_INSERT_RET sht_insert_with_u32(sht_t *t, u32 key, void *value)
{
    return sht_insert_generic(t, &key, sizeof(key), value, murmurhash3_64(&key, sizeof(key)), sht_match_u32);
}

void *sht_find_with_u32(sht_t *t, u32 key)
{
    return sht_find_generic(t, &key, murmurhash3_64(&key, sizeof(key)), sht_match_u32);
}

void *sht_remove_with_u32(sht_t *t, u32 key)
{
    return sht_remove_generic(t, &key, murmurhash3_64(&key, sizeof(key)), sht_match_u32);
}

int sht_match_ipv6(const void *search_key, const void *entry_key)
{
    return memcmp(search_key, entry_key, sizeof(struct in6_addr)) == 0;
}

SHT_INSERT_RET sht_insert_with_ipv6(sht_t *t, const struct in6_addr *key, void *value)
{
    return sht_insert_generic(t, key, sizeof(*key), value, murmurhash3_64(key, sizeof(*key)), sht_match_ipv6);
}

void *sht_find_with_ipv6(sht_t *t, const struct in6_addr *key)
{
    return sht_find_generic(t, key, murmurhash3_64(key, sizeof(*key)), sht_match_ipv6);
}

void *sht_remove_with_ipv6(sht_t *t, const struct in6_addr *key)
{
    return sht_remove_generic(t, key, murmurhash3_64(key, sizeof(*key)), sht_match_ipv6);
}

BOOL_T sht_bucket_visit(sht_bucket_t *b, sht_visitor_f visit, void *env)
{
    unsigned int i;

    for (i = 0; i < b->next_entry; i++) {
        sht_entry_t *e;

        e = &b->entries[i];
        if (visit(env, e->key, (void *)e->value)) {
            return TRUE;
        }
    }

    return FALSE;
}

void sht_visit(sht_t *t, sht_visitor_f visit, void *env)
{
    unsigned int i;

    for (i = 0; i < t->num_buckets; i++) {
        if (sht_bucket_visit(sht_bucket_get(t, i), visit, env)) {
            return;
        }
    }
}

BOOL_T sht_visit_print_str(void *env, const void *key, void *value)
{
    const char *k = key;
    const u32 *v = value;

    printf("%s -> %u\n", k, *v);

    return FALSE;
}

