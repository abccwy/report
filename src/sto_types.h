/*
 * File name: sto_types.h
 *
 * Copyright(C) 2007-2015, A10 Networks Inc. All rights reserved.
 * Software for all A10 products contain trade secrets and confidential
 * information of A10 Networks and its subsidiaries and may not be
 * disclosed, copied, reproduced or distributed to anyone outside of
 * A10 Networks without prior written consent of A10 Networks, Inc.
 */
/****************************************************************************
 *
 * Copyright (C) 2005, A10 Networks Inc. All rights reserved.
 *
 * Description:  Common type definitions.
 *
 * Authors: Zhiruo Cao <jcao@a10networks.com>
 *
 ***************************************************************************/

#if !defined(_STO_TYPES_H)
#define _STO_TYPES_H

//#include <comm_const.h>

typedef signed char __s8;
typedef signed char s8;
typedef unsigned char u8;

typedef signed short __s16;
typedef signed short s16;
typedef unsigned short u16;

typedef signed int __s32;
typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

/*
 * __u types are used to indicate
 * a network order variable.
 */
typedef u8 __u8;
typedef u16 __u16;
typedef u32 __u32;
typedef u64 __u64;

typedef         __u8            u_int8_t;
typedef         __s8            int8_t;
typedef         __u16           u_int16_t;
typedef         __s16           int16_t;
typedef         __u32           u_int32_t;
typedef         __s32           int32_t;

#ifdef A10_DPLANE
#ifndef STO_TYPES_LOFF_T
#define STO_TYPES_LOFF_T
typedef long long               loff_t;
#endif

#ifdef CONFIG_64BIT
typedef u64                     uintptr_t;
typedef s64                     intptr_t;
typedef unsigned long           size_t;
typedef long                    ssize_t;
#else
typedef u32                     uintptr_t;
typedef s32                     intptr_t;
typedef unsigned int            size_t;
typedef int                     ssize_t;
#endif
#endif

#define  KERNEL_LINK_ADDR_LEN  32

/*
///The structure that can hold kernel interface information.
typedef struct
{
    int index; //the index in the array list of a10_kernel_interface_information
    int kernel_ifindex;
    int ipaddr_counter;
    unsigned int kernel_flags;
    unsigned int mtu;
    unsigned int speed;
    char name[KERNEL_IFNAME_SIZE];
    char label[MAX_STO_ASM_MULTIPLE_IP_PER_NIC][KERNEL_IFNAME_SIZE];
    int all_ipaddr[MAX_STO_ASM_MULTIPLE_IP_PER_NIC];
    int all_netmask[MAX_STO_ASM_MULTIPLE_IP_PER_NIC];
    unsigned char dev_addr[KERNEL_LINK_ADDR_LEN];
    int dev_addr_len;
}a10_kernel_interface_information;
*/

#ifdef __cplusplus
#define DI_FIELD_VALUE(field, value) value
#else
#define DI_FIELD_VALUE(field, value) [field] = value
#endif/* __cplusplus */

#endif /* _STO_TYPES_H */
