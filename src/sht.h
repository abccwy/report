/*
 * File name: sht.h
 *
 * Copyright(C) 2007-2016, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */
#ifndef _SHT_H_
#define _SHT_H_

//#include <sto_types.h>
#include "sto_types.h"
#include <spinlock.h>

//typedef unsigned int u32;
//typedef unsigned long long u64;
typedef unsigned char BOOL_T;

struct simple_hash_table;
typedef struct simple_hash_table sht_t;

struct simple_hash_table_lockable {
    sht_t *ht;
    spinlock_t lock;
} __attribute__((packed));
typedef struct simple_hash_table_lockable sht_lock_t;

typedef enum {
    SHT_INSERT_SUCCESS = 0,
    SHT_INSERT_FOUND,
    SHT_INSERT_OOM,
} SHT_INSERT_RET;

struct sht_global {
    unsigned int mem_alloc;
    unsigned int mem_free;
} __attribute__((packed));
typedef struct sht_global sht_global_t;

sht_global_t g_sht;

struct sht_entry {
    const void *key;
    void *value;
} __attribute__((packed));
typedef struct sht_entry sht_entry_t;

struct sht_bucket {
    u32 max_entries;
    u32 next_entry;
    sht_entry_t *entries;
} __attribute__((__packed__));
typedef struct sht_bucket sht_bucket_t;

struct simple_hash_table {
    u32 num_buckets;
    sht_bucket_t *buckets;
    u32 num_entries;
} __attribute__((__packed__));

#define SHT_BUCKET_SIZE_DEFAULT 4


/* bool semantics, i.e. == TRUE means a match */
typedef int (*sht_match_f)(const void *search_key, const void *entry_key);
/* return TRUE if stopping the walk early */
typedef BOOL_T(*sht_visitor_f)(void *env, const void *key, void *value);

unsigned int sht_num_entries(const sht_t *t);
sht_t *sht_alloc(u32 num_buckets);
void sht_free(sht_t *t);
void sht_reset(sht_t *t);
SHT_INSERT_RET sht_insert_generic(sht_t *t, const void *key, unsigned int key_len, void *value, u64 key_hash, sht_match_f key_match);
void *sht_find_generic(sht_t *t, const void *search_key, u64 key_hash, sht_match_f key_match);
void *sht_remove_generic(sht_t *t, const void *search_key, u64 key_hash, sht_match_f key_match);
sht_bucket_t *sht_bucket_get(sht_t *t, u64 hash);
BOOL_T sht_bucket_visit(sht_bucket_t *b, sht_visitor_f visit, void *env);


SHT_INSERT_RET sht_insert_with_str(sht_t *t, const char *key, void *value);
void *sht_find_with_str(sht_t *t, const char *key);
void *sht_remove_with_str(sht_t *t, const char *key);

SHT_INSERT_RET sht_insert_with_u32(sht_t *t, u32 key, void *value);
void *sht_find_with_u32(sht_t *t, u32 key);
void *sht_remove_with_u32(sht_t *t, u32 key);

struct in6_addr;
SHT_INSERT_RET sht_insert_with_ipv6(sht_t *t, const struct in6_addr *key, void *value);
void *sht_find_with_ipv6(sht_t *t, const struct in6_addr *key);
void *sht_remove_with_ipv6(sht_t *t, const struct in6_addr *key);

void sht_visit(sht_t *t, sht_visitor_f visit, void *env);

#endif /* _SHT_H_ */
