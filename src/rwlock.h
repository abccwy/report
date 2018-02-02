/*
 * File name: rwlock.h
 *
 * Copyright(C) 2007-2013, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */
/* include/asm-i386/rwlock.h
 *
 *  Helpers used by both rw spinlocks and rw semaphores.
 *
 *  Based in part on code from semaphore.h and
 *  spinlock.h Copyright 1996 Linus Torvalds.
 *
 *  Copyright 1999 Red Hat, Inc.
 *
 *  Written by Benjamin LaHaise.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 */
#ifndef _ASM_I386_RWLOCK_H
#define _ASM_I386_RWLOCK_H

#define RW_LOCK_BIAS         0x01000000
#define RW_LOCK_BIAS_STR    "0x01000000"

#ifdef CONFIG_64BIT
# define LOCK_PTR_REG "D"
#else
# define LOCK_PTR_REG "a"
#endif

/*
 * Read-write spinlocks, allowing multiple readers
 * but only one writer.
 *
 * NOTE! it is quite common to have readers in interrupts
 * but no interrupt writers. For those circumstances we
 * can "mix" irq-safe locks - any writer needs to get a
 * irq-safe write-lock, but readers can get non-irqsafe
 * read-locks.
 */
typedef struct {
    volatile unsigned int lock;
#if SPINLOCK_DEBUG
    unsigned magic;
#endif
} rwlock_t;

#define RWLOCK_MAGIC    0xdeaf1eed

#if SPINLOCK_DEBUG
#define RWLOCK_MAGIC_INIT   , RWLOCK_MAGIC
#else
#define RWLOCK_MAGIC_INIT   /* */
#endif

#define RW_LOCK_UNLOCKED (rwlock_t) { RW_LOCK_BIAS RWLOCK_MAGIC_INIT }

#define DEFINE_RWLOCK(x)    rwlock_t x = RW_LOCK_UNLOCKED

#define rwlock_init(x)  do { *(x) = RW_LOCK_UNLOCKED; } while(0)

/*
 * On x86, we implement read-write locks as a 32-bit counter
 * with the high bit (sign) being the "contended" bit.
 *
 * The inline assembly is non-obvious. Think about it.
 *
 * Changed to use the same technique as rw semaphores.  See
 * semaphore.h for details.  -ben
 */
/* the spinlock helpers are in arch/i386/kernel/semaphore.c */

extern void __write_lock_failed(rwlock_t *rw);
extern void __read_lock_failed(rwlock_t *rw);

static inline void __raw_read_lock(rwlock_t *rw)
{
    asm volatile("lock ; " " subl $1,(%0)\n\t"
                 "jns 1f\n"
                 "call __read_lock_failed\n\t"
                 "1:\n"
                 ::LOCK_PTR_REG(rw) : "memory");
}

static inline void __raw_write_lock(rwlock_t *rw)
{
    asm volatile("lock ; " " subl %1,(%0)\n\t"
                 "jz 1f\n"
                 "call __write_lock_failed\n\t"
                 "1:\n"
                 ::LOCK_PTR_REG(rw), "i"(RW_LOCK_BIAS) : "memory");
}

static inline void read_lock(rwlock_t *rw)
{
#if SPINLOCK_DEBUG

    if (rw->magic != RWLOCK_MAGIC) {
        BUG();
    }

#endif
    __raw_read_lock(rw);
}

static inline void write_lock(rwlock_t *rw)
{
#if SPINLOCK_DEBUG

    if (rw->magic != RWLOCK_MAGIC) {
        BUG();
    }

#endif
    __raw_write_lock(rw);
}

#define read_unlock(rw)     asm volatile("lock ; incl %0" :"=m" ((rw)->lock) : : "memory")
#define write_unlock(rw)    asm volatile("lock ; addl $" RW_LOCK_BIAS_STR ",%0":"=m" ((rw)->lock) : : "memory")

static inline int read_trylock(rwlock_t *lock)
{
    atomic_t *count = (atomic_t *)lock;

    atomic_dec(count);

    if (atomic_read(count) >= 0) {
        return 1;
    }

    atomic_inc(count);
    return 0;
}

static inline int write_trylock(rwlock_t *lock)
{
    atomic_t *count = (atomic_t *)lock;

    if (atomic_sub_and_test(RW_LOCK_BIAS, count)) {
        return 1;
    }

    atomic_add(RW_LOCK_BIAS, count);
    return 0;
}

#endif
