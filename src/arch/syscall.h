/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _LIBFINGC_SYSCALL_H_
#define _LIBFINGC_SYSCALL_H_

#include <stdint.h>

uint64_t __libfingc_syscall_0(uint64_t);

uint64_t __libfingc_syscall_1(uint64_t, uint64_t);

uint64_t __libfingc_syscall_2(uint64_t, uint64_t, uint64_t);

uint64_t __libfingc_syscall_3(uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t __libfingc_syscall_4(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

#define brk(addr) (void *)__libfingc_syscall_1((uint64_t)(addr), 12)

#endif /* _LIBFINGC_SYSCALL_H_ */