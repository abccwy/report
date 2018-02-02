/*
 * File name: spinlock.h
 *
 * Copyright(C) 2007-2016, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */
#ifndef __ASM_SPINLOCK_H
#define __ASM_SPINLOCK_H

//#include <asm/atomic.h>
#include "atomic.h"

#define LOCK_SECTION_NAME                       \
        ".text.lock.A10_USR_SPINLOCK"

#define LOCK_SECTION_START(extra)               \
        ".subsection 1\n\t"                     \
        extra                                   \
        ".ifndef " LOCK_SECTION_NAME "\n\t"     \
        LOCK_SECTION_NAME ":\n\t"               \
        ".endif\n\t"

#define LOCK_SECTION_END                        \
        ".previous\n\t"



/* It seems that people are forgetting to
 * initialize their spinlocks properly, tsk tsk.
 * Remember to turn this off in 2.4. -ben
 */
#undef CONFIG_DEBUG_SPINLOCK

#if defined(CONFIG_DEBUG_SPINLOCK)
#define SPINLOCK_DEBUG  1
#else
#define SPINLOCK_DEBUG  0
#endif

/*
 * Your basic SMP spinlocks, allowing only a single CPU anywhere
 */

typedef struct {
    volatile unsigned int lock;
#if SPINLOCK_DEBUG
    unsigned magic;
#endif
} spinlock_t;

#define SPINLOCK_MAGIC  0xdead4ead

#if SPINLOCK_DEBUG
#define SPINLOCK_MAGIC_INIT , SPINLOCK_MAGIC
#else
#define SPINLOCK_MAGIC_INIT /* */
#endif

#define SPIN_LOCK_UNLOCKED (spinlock_t) { 1 SPINLOCK_MAGIC_INIT }
#define DEFINE_SPINLOCK(x)  spinlock_t x = SPIN_LOCK_UNLOCKED

#define spin_lock_init(x)   do { *(x) = SPIN_LOCK_UNLOCKED; } while(0)

/*
 * Simple spin lock operations.  There are two variants, one clears IRQ's
 * on the local processor, one does not.
 *
 * We make no fairness assumptions. They have a cost.
 */

#define spin_is_locked(x)   (*(volatile signed char *)(&(x)->lock) <= 0)
#define spin_unlock_wait(x) do { barrier(); } while(spin_is_locked(x))

#define spin_lock_string    \
    "\n1:\t"                \
    "lock ; decb %0\n\t"    \
    "js 2f\n"               \
    LOCK_SECTION_START("")  \
    "2:\t"                  \
    "cmpb $0,%0\n\t"        \
    "rep;nop\n\t"           \
    "jle 2b\n\t"            \
    "jmp 1b\n"              \
    LOCK_SECTION_END

/*
 * This works. Despite all the confusion.
 * (except on PPro SMP or if we are using OOSTORE)
 * (PPro errata 66, 92)
 */

#if !defined(CONFIG_X86_OOSTORE) && !defined(CONFIG_X86_PPRO_FENCE)

#define spin_unlock_string  \
    "movb $1,%0"            \
        :"=m" (lock->lock) : : "memory"


static inline void spin_unlock(spinlock_t *lock)
{
#if SPINLOCK_DEBUG

    if (lock->magic != SPINLOCK_MAGIC) {
        BUG();
    }

    if (!spin_is_locked(lock)) {
        BUG();
    }

#endif
    __asm__ __volatile__(
        spin_unlock_string
    );
}

#else

#define spin_unlock_string                  \
    "xchgb %b0, %1"                         \
        :"=q" (oldval), "=m" (lock->lock)   \
        :"0" (oldval) : "memory"

static inline void spin_unlock(spinlock_t *lock)
{
    char oldval = 1;
#if SPINLOCK_DEBUG

    if (lock->magic != SPINLOCK_MAGIC) {
        BUG();
    }

    if (!spin_is_locked(lock)) {
        BUG();
    }

#endif
    __asm__ __volatile__(
        spin_unlock_string
    );
}

#endif

static inline int spin_trylock(spinlock_t *lock)
{
    char oldval;
    __asm__ __volatile__(
        "xchgb %b0,%1"
        :"=q"(oldval), "=m"(lock->lock)
        :"0"(0) : "memory");
    return oldval > 0;
}

static inline void spin_lock(spinlock_t *lock)
{
#if SPINLOCK_DEBUG
    __label__ here;
here:

    if (lock->magic != SPINLOCK_MAGIC) {
        //printf("eip: %p\n", &&here);
        BUG();
    }

#endif
    __asm__ __volatile__(
        spin_lock_string
        :"=m"(lock->lock) : : "memory");
}

//#include <asm/rwlock.h>
#include "rwlock.h"

#define spin_lock8_string   \
    "\n1:\t"                \
    "lock ; decb %b0\n\t"   \
    "js 2f\n"               \
    LOCK_SECTION_START("")  \
    "2:\t"                  \
    "cmpb $0,%b0\n\t"       \
    "rep;nop\n\t"           \
    "jle 2b\n\t"            \
    "jmp 1b\n"              \
    LOCK_SECTION_END

typedef struct spinlock8 {
    volatile unsigned char lock;
} __attribute__((__packed__)) spinlock8_t;

static inline void spin_lock8_init(spinlock8_t *lock)
{
    lock->lock = 1;
}

static inline int spin_trylock8(spinlock8_t *lock)
{
    char oldval;
    __asm__ __volatile__(
        "xchgb %b0,%1"
        :"=q"(oldval), "=m"(lock->lock)
        :"0"(0) : "memory");
    return oldval > 0;
}

static inline void spin_lock8(spinlock8_t *lock)
{
    __asm__ __volatile__(
        spin_lock8_string
        :"=m"(lock->lock) : : "memory");
}

static inline void spin_unlock8(spinlock8_t *lock)
{
    __asm__ __volatile__(
        spin_unlock_string
    );
}

typedef struct spinlock32 {
    volatile unsigned int lock;
} __attribute__((__packed__)) spinlock32_t;

static inline void spin_lock32_init(spinlock32_t *lock)
{
    lock->lock = 1;
}

static inline void spin_lock32(spinlock32_t *lock)
{
    __asm__ __volatile__(
        spin_lock_string
        :"=m"(lock->lock) : : "memory");
}

static inline void spin_unlock32(spinlock32_t *lock)
{
    __asm__ __volatile__(
        spin_unlock_string
    );
}


#endif /* __ASM_SPINLOCK_H */

