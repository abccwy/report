/*
 * File name: a10_hash.h
 *
 * Copyright(C) 2007-2016, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */

#if !defined(_A10_HASH_H_)
#define _A10_HASH_H_

//#include <sto_types.h>
#include "sto_types.h"

static inline u64 rotl64(u64 x, u8 bits)
{
    __asm__(
        "rolq %%cl, %0"
        : "=g"(x)
        : "0"(x), "c"(bits)
    );

    return x;
}

static inline u64 fmix64(u64 k)
{
    k ^= k >> 33;
    k *= 0xff51afd7ed558ccdULL;
    k ^= k >> 33;
    k *= 0xc4ceb9fe1a85ec53ULL;
    k ^= k >> 33;

    return k;
}

static inline u64 murmurhash3_64(const void *key, unsigned int len)
{
    unsigned int i;
    const u8 *data = key;
    const unsigned int nblocks = len / 16;

#define MURMURHASH_SEED 7
    u64 h1 = MURMURHASH_SEED;
    u64 h2 = MURMURHASH_SEED;

    const u64 c1 = 0x87c37b91114253d5ULL;
    const u64 c2 = 0x4cf5ad432745937fULL;

    const u64 *blocks = (const u64 *)(data);

    for (i = 0; i < nblocks; i++) {
        u64 k1 = blocks[i * 2 + 0];
        u64 k2 = blocks[i * 2 + 1];

        k1 *= c1;
        k1  = rotl64(k1, 31);
        k1 *= c2;
        h1 ^= k1;

        h1 = rotl64(h1, 27);
        h1 += h2;
        h1 = h1 * 5 + 0x52dce729;

        k2 *= c2;
        k2  = rotl64(k2, 33);
        k2 *= c1;
        h2 ^= k2;

        h2 = rotl64(h2, 31);
        h2 += h1;
        h2 = h2 * 5 + 0x38495ab5;
    }

    const u8 *tail = (const u8 *)(data + nblocks * 16);

    u64 k1 = 0;
    u64 k2 = 0;

    switch (len & 15) {
        case 15:
            k2 ^= ((u64)tail[14]) << 48;
        case 14:
            k2 ^= ((u64)tail[13]) << 40;
        case 13:
            k2 ^= ((u64)tail[12]) << 32;
        case 12:
            k2 ^= ((u64)tail[11]) << 24;
        case 11:
            k2 ^= ((u64)tail[10]) << 16;
        case 10:
            k2 ^= ((u64)tail[ 9]) << 8;
        case  9:
            k2 ^= ((u64)tail[ 8]) << 0;
            k2 *= c2;
            k2  = rotl64(k2, 33);
            k2 *= c1;
            h2 ^= k2;

        case  8:
            k1 ^= ((u64)tail[ 7]) << 56;
        case  7:
            k1 ^= ((u64)tail[ 6]) << 48;
        case  6:
            k1 ^= ((u64)tail[ 5]) << 40;
        case  5:
            k1 ^= ((u64)tail[ 4]) << 32;
        case  4:
            k1 ^= ((u64)tail[ 3]) << 24;
        case  3:
            k1 ^= ((u64)tail[ 2]) << 16;
        case  2:
            k1 ^= ((u64)tail[ 1]) << 8;
        case  1:
            k1 ^= ((u64)tail[ 0]) << 0;
            k1 *= c1;
            k1  = rotl64(k1, 31);
            k1 *= c2;
            h1 ^= k1;
    }

    //----------
    // finalization

    h1 ^= len;
    h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 = fmix64(h1);
    h2 = fmix64(h2);

    h1 += h2;
    h2 += h1;

    /**
     * the normal one returns h1 and h2 together as a 128-bit hash
     * we only want 64-bit return for now
     */
    return h1;
}

/**
 * Get 32-bit Murmur3 hash.
 *
 * @param data      source data
 * @param nbytes    size of data
 *
 * @return 32-bit unsigned hash value.
 *
 * @code
 *  uint32_t hashval = qhashmurmur3_32((void*)"hello", 5);
 * @endcode
 *
 * @code
 *  MurmurHash3 was created by Austin Appleby  in 2008. The initial
 *  implementation was published in C++ and placed in the public.
 *    https://sites.google.com/site/murmurhash/
 *  Seungyoung Kim has ported its implementation into C language
 *  in 2012 and published it as a part of qLibc component.
 * @endcode
 */
static inline u32 qhashmurmur3_32(const void *data, unsigned int nbytes)
{
    if (data == NULL || nbytes == 0) {
        return 0;
    }

    const u32 c1 = 0xcc9e2d51;
    const u32 c2 = 0x1b873593;

    const int nblocks = nbytes / 4;
    const u32 *blocks = (const u32 *)(data);
    const u8 *tail = (const u8 *)(data + (nblocks * 4));

    u32 h = 0;

    int i;
    u32 k;
    for (i = 0; i < nblocks; i++) {
        k = blocks[i];

        k *= c1;
        k = (k << 15) | (k >> (32 - 15));
        k *= c2;

        h ^= k;
        h = (h << 13) | (h >> (32 - 13));
        h = (h * 5) + 0xe6546b64;
    }

    k = 0;
    switch (nbytes & 3) {
        case 3:
            k ^= tail[2] << 16;
        case 2:
            k ^= tail[1] << 8;
        case 1:
            k ^= tail[0];
            k *= c1;
            k = (k << 15) | (k >> (32 - 15));
            k *= c2;
            h ^= k;
    };

    h ^= nbytes;

    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
}

#endif /* _A10_HASH_H_ */


