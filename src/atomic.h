/*
 * File name: atomic.h
 *
 * Copyright(C) 2007-2013, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */
#ifndef __ARCH_I386_ATOMIC__
#define __ARCH_I386_ATOMIC__

/*
 * Atomic operations that C can't guarantee us.  Useful for
 * resource counting etc..
 */


#ifndef CONFIG_SMP
#define CONFIG_SMP
#endif

#ifdef CONFIG_SMP
#define LOCK "lock ; "
#else
#define LOCK ""
#endif

/*
 * Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
typedef struct {
    volatile int counter;
} atomic_t;
typedef struct {
    volatile signed short counter;
} __attribute__((__packed__)) atomic16_t;
typedef struct {
    volatile signed char counter;
} __attribute__((__packed__)) atomic8_t;

#define ATOMIC_INIT(i)  { (i) }

/**
 * atomic_read - read atomic variable
 * @v: pointer of type atomic_t
 *
 * Atomically reads the value of @v.
 */
#define atomic_read(v)      ((v)->counter)
#define atomic16_read(v)    ((v)->counter)
#define atomic8_read(v)     ((v)->counter)

// Return unsigned values
static inline unsigned int uatomic_read(const atomic_t *v)
{
    return ((unsigned int)(v->counter));
}

static inline unsigned short uatomic16_read(const atomic16_t *v)
{
    return ((unsigned short)(v->counter));
}

static inline unsigned char uatomic8_read(const atomic8_t *v)
{
    return ((unsigned char)(v->counter));
}

/**
 * atomic_set - set atomic variable
 * @v: pointer of type atomic_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
#define atomic_set(v,i)     (((v)->counter) = (i))
#define atomic16_set(v,i)   (((v)->counter) = (i))
#define atomic8_set(v,i)    (((v)->counter) = (i))

/**
 * atomic_add - add integer to atomic variable
 * @i: integer value to add
 * @v: pointer of type atomic_t
 *
 * Atomically adds @i to @v.
 */
static __inline__ void atomic_add(int i, atomic_t *v)
{
    __asm__ __volatile__(
        LOCK "addl %1,%0"
        :"=m"(v->counter)
        :"ir"(i), "m"(v->counter));
}

static __inline__ void atomic16_add(signed short i, atomic16_t *v)
{
    __asm__ __volatile__(
        LOCK "addw %1,%0"
        :"=m"(v->counter)
        :"ir"(i), "m"(v->counter));
}

static __inline__ void atomic8_add(signed char i, atomic8_t *v)
{
    __asm__ __volatile__(
        LOCK "addb %1,%0"
        :"=m"(v->counter)
        :"ir"(i), "m"(v->counter));
}

/**
 * atomic_sub - subtract the atomic variable
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 *
 * Atomically subtracts @i from @v.
 */
static __inline__ void atomic_sub(int i, atomic_t *v)
{
    __asm__ __volatile__(
        LOCK "subl %1,%0"
        :"=m"(v->counter)
        :"ir"(i), "m"(v->counter));
}

static __inline__ void atomic16_sub(signed short i, atomic16_t *v)
{
    __asm__ __volatile__(
        LOCK "subw %1,%0"
        :"=m"(v->counter)
        :"ir"(i), "m"(v->counter));
}

static __inline__ void atomic8_sub(signed char i, atomic8_t *v)
{
    __asm__ __volatile__(
        LOCK "subb %1,%0"
        :"=m"(v->counter)
        :"ir"(i), "m"(v->counter));
}

/**
 * atomic_sub_and_test - subtract value from variable and test result
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 *
 * Atomically subtracts @i from @v and returns
 * true if the result is zero, or false for all
 * other cases.
 */
static __inline__ int atomic_sub_and_test(int i, atomic_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "subl %2,%0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"ir"(i), "m"(v->counter) : "memory");
    return c;
}

static __inline__ int atomic16_sub_and_test(signed short i, atomic16_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "subw %2,%0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"ir"(i), "m"(v->counter) : "memory");
    return c;
}

static __inline__ int atomic8_sub_and_test(signed char i, atomic8_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "subb %2,%0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"ir"(i), "m"(v->counter) : "memory");
    return c;
}

/**
 * atomic_inc - increment atomic variable
 * @v: pointer of type atomic_t
 *
 * Atomically increments @v by 1.
 */
static __inline__ void atomic_inc(atomic_t *v)
{
    __asm__ __volatile__(
        LOCK "incl %0"
        :"=m"(v->counter)
        :"m"(v->counter));
}

static __inline__ void atomic16_inc(atomic16_t *v)
{
    __asm__ __volatile__(
        LOCK "incw %0"
        :"=m"(v->counter)
        :"m"(v->counter));
}

static __inline__ void atomic8_inc(atomic8_t *v)
{
    __asm__ __volatile__(
        LOCK "incb %0"
        :"=m"(v->counter)
        :"m"(v->counter));
}

/**
 * atomic_dec - decrement atomic variable
 * @v: pointer of type atomic_t
 *
 * Atomically decrements @v by 1.
 */
static __inline__ void atomic_dec(atomic_t *v)
{
    __asm__ __volatile__(
        LOCK "decl %0"
        :"=m"(v->counter)
        :"m"(v->counter));
}

static __inline__ void atomic16_dec(atomic16_t *v)
{
    __asm__ __volatile__(
        LOCK "decw %0"
        :"=m"(v->counter)
        :"m"(v->counter));
}
static __inline__ void atomic8_dec(atomic8_t *v)
{
    __asm__ __volatile__(
        LOCK "decb %0"
        :"=m"(v->counter)
        :"m"(v->counter));
}

/**
 * atomic_dec_and_test - decrement and test
 * @v: pointer of type atomic_t
 *
 * Atomically decrements @v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.
 */
static __inline__ int atomic_dec_and_test(atomic_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "decl %0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"m"(v->counter) : "memory");
    return c != 0;
}

static __inline__ int atomic16_dec_and_test(atomic16_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "decw %0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"m"(v->counter) : "memory");
    return c != 0;
}

static __inline__ int atomic8_dec_and_test(atomic8_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "decb %0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"m"(v->counter) : "memory");
    return c != 0;
}

/**
 * atomic_inc_and_test - increment and test
 * @v: pointer of type atomic_t
 *
 * Atomically increments @v by 1
 * and returns true if the result is zero, or false for all
 * other cases.
 */
static __inline__ int atomic_inc_and_test(atomic_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "incl %0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"m"(v->counter) : "memory");
    return c != 0;
}

static __inline__ int atomic16_inc_and_test(atomic16_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "incw %0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"m"(v->counter) : "memory");
    return c != 0;
}

static __inline__ int atomic8_inc_and_test(atomic8_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "incb %0; sete %1"
        :"=m"(v->counter), "=qm"(c)
        :"m"(v->counter) : "memory");
    return c != 0;
}

/**
 * atomic_add_negative - add and test if negative
 * @v: pointer of type atomic_t
 * @i: integer value to add
 *
 * Atomically adds @i to @v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.
 */
static __inline__ int atomic_add_negative(int i, atomic_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "addl %2,%0; sets %1"
        :"=m"(v->counter), "=qm"(c)
        :"ir"(i), "m"(v->counter) : "memory");
    return c;
}

static __inline__ int atomic16_add_negative(signed short i, atomic16_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "addw %2,%0; sets %1"
        :"=m"(v->counter), "=qm"(c)
        :"ir"(i), "m"(v->counter) : "memory");
    return c;
}

static __inline__ int atomic8_add_negative(signed char i, atomic8_t *v)
{
    unsigned char c;

    __asm__ __volatile__(
        LOCK "addb %2,%0; sets %1"
        :"=m"(v->counter), "=qm"(c)
        :"ir"(i), "m"(v->counter) : "memory");
    return c;
}

/**
 * atomic_add_return - add and return
 * @v: pointer of type atomic_t
 * @i: integer value to add
 *
 * Atomically adds @i to @v and returns @i + @v
 */
static __inline__ int atomic_add_return(int i, atomic_t *v)
{
    int __i;
#ifdef CONFIG_M386

    if (unlikely(boot_cpu_data.x86 == 3)) {
        goto no_xadd;
    }

#endif
    /* Modern 486+ processor */
    __i = i;
    __asm__ __volatile__(
        LOCK "xaddl %0, %1;"
        :"=r"(i)
        :"m"(v->counter), "0"(i));
    return i + __i;

#ifdef CONFIG_M386
no_xadd: /* Legacy 386 processor */
    local_irq_disable();
    __i = atomic_read(v);
    atomic_set(v, i + __i);
    local_irq_enable();
    return i + __i;
#endif
}

static __inline__ signed short atomic16_add_return(signed short i, atomic16_t *v)
{
    signed short __i;
#ifdef CONFIG_M386

    if (unlikely(boot_cpu_data.x86 == 3)) {
        goto no_xadd;
    }

#endif
    /* Modern 486+ processor */
    __i = i;
    __asm__ __volatile__(
        LOCK "xaddw %0, %1;"
        :"=r"(i)
        :"m"(v->counter), "0"(i));
    return i + __i;

#ifdef CONFIG_M386
no_xadd: /* Legacy 386 processor */
    local_irq_disable();
    __i = atomic16_read(v);
    atomic16_set(v, i + __i);
    local_irq_enable();
    return i + __i;
#endif
}

static __inline__ signed char atomic8_add_return(signed char i, atomic8_t *v)
{
    signed char __i;
#ifdef CONFIG_M386

    if (unlikely(boot_cpu_data.x86 == 3)) {
        goto no_xadd;
    }

#endif
    /* Modern 486+ processor */
    __i = i;
    __asm__ __volatile__(
        LOCK "xaddb %0, %1;"
        :"=r"(i)
        :"m"(v->counter), "0"(i));
    return i + __i;

#ifdef CONFIG_M386
no_xadd: /* Legacy 386 processor */
    local_irq_disable();
    __i = atomic8_read(v);
    atomic8_set(v, i + __i);
    local_irq_enable();
    return i + __i;
#endif
}

static __inline__ int atomic_sub_return(int i, atomic_t *v)
{
    return atomic_add_return(-i, v);
}

static __inline__ signed short atomic16_sub_return(signed short i, atomic16_t *v)
{
    return atomic16_add_return(-i, v);
}

static __inline__ signed char atomic8_sub_return(signed char i, atomic8_t *v)
{
    return atomic8_add_return(-i, v);
}

#define atomic_inc_return(v)    (atomic_add_return(1,v))
#define atomic16_inc_return(v)  (atomic16_add_return(1,v))
#define atomic8_inc_return(v)   (atomic8_add_return(1,v))
#define atomic_dec_return(v)    (atomic_sub_return(1,v))
#define atomic16_dec_return(v)  (atomic16_sub_return(1,v))
#define atomic8_dec_return(v)   (atomic8_sub_return(1,v))

/* These are x86-specific, used by some header files */
#define atomic_clear_mask(mask, addr)   \
__asm__ __volatile__(LOCK "andl %0,%1"  \
: : "r" (~(mask)),"m" (*addr) : "memory")

#define atomic16_clear_mask(mask, addr)     \
__asm__ __volatile__(LOCK "andw %0,%1"      \
: : "r" (~(mask)),"m" (*addr) : "memory")

#define atomic8_clear_mask(mask, addr)  \
__asm__ __volatile__(LOCK "andb %0,%1"  \
: : "r" (~(mask)),"m" (*addr) : "memory")

#define atomic_set_mask(mask, addr)     \
__asm__ __volatile__(LOCK "orl %0,%1"   \
: : "r" (mask),"m" (*(addr)) : "memory")

#define atomic16_set_mask(mask, addr)   \
__asm__ __volatile__(LOCK "orw %0,%1"   \
: : "r" (mask),"m" (*(addr)) : "memory")

#define atomic8_set_mask(mask, addr)    \
__asm__ __volatile__(LOCK "orb %0,%1"   \
: : "r" (mask),"m" (*(addr)) : "memory")

/*
 * To support atomic64_t type, we need a 64 bit platform.
 *
 * The following is a list of definition for atomic64_t operations.
 * On a 64 bit platform a real genuine 64 bit operation is supported.
 * On a 32 bit platform the operation will behave like the 32 bit
 * counterpart (like atomic_t operation).
 */


/*
 * common portion of the atomic64_t both for 32 bit and 64 bit
 */

#define ATOMIC64_INIT(i)    { (i) }

/**
 * atomic64_read - read atomic64 variable
 * @v: pointer of type atomic64_t
 *
 * Atomically reads the value of @v.
 * Doesn't imply a read memory barrier.
 */
#define atomic64_read(v)        ((v)->counter)

/**
 * atomic64_set - set atomic64 variable
 * @v: pointer to type atomic64_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
#define atomic64_set(v, i)      (((v)->counter) = (i))


#ifdef CONFIG_64BIT
/* An 64bit atomic type */
typedef struct {
    volatile long counter;
} atomic64_t;

/**
 * atomic64_add - add integer to atomic64 variable
 * @i: integer value to add
 * @v: pointer to type atomic64_t
 *
 * Atomically adds @i to @v.
 */
static inline void atomic64_add(long i, atomic64_t *v)
{
    asm volatile(LOCK "addq %1,%0"
                 : "=m"(v->counter)
                 : "ir"(i), "m"(v->counter));
}

/**
 * atomic64_sub - subtract the atomic64 variable
 * @i: integer value to subtract
 * @v: pointer to type atomic64_t
 *
 * Atomically subtracts @i from @v.
 */
static inline void atomic64_sub(long i, atomic64_t *v)
{
    asm volatile(LOCK "subq %1,%0"
                 : "=m"(v->counter)
                 : "ir"(i), "m"(v->counter));
}

/**
 * atomic64_sub_and_test - subtract value from variable and test result
 * @i: integer value to subtract
 * @v: pointer to type atomic64_t
 *
 * Atomically subtracts @i from @v and returns
 * true if the result is zero, or false for all
 * other cases.
 */
static inline int atomic64_sub_and_test(long i, atomic64_t *v)
{
    unsigned char c;

    asm volatile(LOCK "subq %2,%0; sete %1"
                 : "=m"(v->counter), "=qm"(c)
                 : "ir"(i), "m"(v->counter) : "memory");
    return c;
}

/**
 * atomic64_inc - increment atomic64 variable
 * @v: pointer to type atomic64_t
 *
 * Atomically increments @v by 1.
 */
static inline void atomic64_inc(atomic64_t *v)
{
    asm volatile(LOCK "incq %0"
                 : "=m"(v->counter)
                 : "m"(v->counter));
}

/**
 * atomic64_dec - decrement atomic64 variable
 * @v: pointer to type atomic64_t
 *
 * Atomically decrements @v by 1.
 */
static inline void atomic64_dec(atomic64_t *v)
{
    asm volatile(LOCK "decq %0"
                 : "=m"(v->counter)
                 : "m"(v->counter));
}

/**
 * atomic64_dec_and_test - decrement and test
 * @v: pointer to type atomic64_t
 *
 * Atomically decrements @v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.
 */
static inline int atomic64_dec_and_test(atomic64_t *v)
{
    unsigned char c;

    asm volatile(LOCK "decq %0; sete %1"
                 : "=m"(v->counter), "=qm"(c)
                 : "m"(v->counter) : "memory");
    return c != 0;
}

/**
 * atomic64_inc_and_test - increment and test
 * @v: pointer to type atomic64_t
 *
 * Atomically increments @v by 1
 * and returns true if the result is zero, or false for all
 * other cases.
 */
static inline int atomic64_inc_and_test(atomic64_t *v)
{
    unsigned char c;

    asm volatile(LOCK "incq %0; sete %1"
                 : "=m"(v->counter), "=qm"(c)
                 : "m"(v->counter) : "memory");
    return c != 0;
}

/**
 * atomic64_add_negative - add and test if negative
 * @i: integer value to add
 * @v: pointer to type atomic64_t
 *
 * Atomically adds @i to @v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.
 */
static inline int atomic64_add_negative(long i, atomic64_t *v)
{
    unsigned char c;

    asm volatile(LOCK "addq %2,%0; sets %1"
                 : "=m"(v->counter), "=qm"(c)
                 : "ir"(i), "m"(v->counter) : "memory");
    return c;
}

/**
 * atomic64_add_return - add and return
 * @i: integer value to add
 * @v: pointer to type atomic64_t
 *
 * Atomically adds @i to @v and returns @i + @v
 */
static inline long atomic64_add_return(long i, atomic64_t *v)
{
    long __i = i;
    asm volatile(LOCK "xaddq %0, %1;"
                 : "+r"(i), "+m"(v->counter)
                 : : "memory");
    return i + __i;
}

static inline long atomic64_sub_return(long i, atomic64_t *v)
{
    return atomic64_add_return(-i, v);
}

#define atomic64_inc_return(v)  (atomic64_add_return(1, (v)))
#define atomic64_dec_return(v)  (atomic64_sub_return(1, (v)))

#else

/* An 64bit atomic type */
typedef atomic_t atomic64_t;

#define atomic64_add(i, v)      (atomic_add(i, v))
#define atomic64_sub(i, v)      (atomic_sub(i, v))
#define atomic64_sub_and_test(i, v) (atomic_sub_and_test(i, v))
#define atomic64_inc(v)         (atomic_inc(v))
#define atomic64_dec(v)         (atomic_dec(v))
#define atomic64_dec_and_test(v)    (atomic_dec_and_test(v))
#define atomic64_inc_and_test(v)    (atomic_inc_and_test(v))
#define atomic64_add_negative(i, v) (atomic_add_negative(i, v))
#define atomic64_add_return(i, v)   (atomic_add_return(i, v))
#define atomic64_sub_return(i, v)   (atomic_sub_return(i, v))
#define atomic64_inc_return(v)      (atomic_add_return(1, (v)))
#define atomic64_dec_return(v)      (atomic_sub_return(1, (v)))

#endif /* CONFIG_64BIT */

/* Atomic operations are already serializing on x86 */
#define smp_mb__before_atomic_dec() barrier()
#define smp_mb__after_atomic_dec()  barrier()
#define smp_mb__before_atomic_inc() barrier()
#define smp_mb__after_atomic_inc()  barrier()

#endif
