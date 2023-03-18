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

uint64_t __libfingc_syscall_4(uint64_t, uint64_t, uint64_t, uint64_t,
			      uint64_t);

uint64_t __libfingc_syscall_5(uint64_t, uint64_t, uint64_t, uint64_t,
			      uint64_t, uint64_t);

uint64_t __libfingc_syscall_6(uint64_t, uint64_t, uint64_t, uint64_t,
			      uint64_t, uint64_t, uint64_t);

static inline void *__mmap(void *addr, size_t len, int prot,
			   int flags, int fd, size_t off)
{
	uint64_t __addr = (uint64_t)addr;
	uint64_t __len = (uint64_t)len;
	uint64_t __prot = (uint64_t)prot;
	uint64_t __flags = (uint64_t)flags;
	uint64_t __fd = (uint64_t)fd;
	uint64_t __off = (uint64_t)off;

	return (void *)__libfingc_syscall_6(__addr, __len, __prot, __flags, __fd, __off, 9);
}

static inline int __munmap(void *addr, size_t len)
{
	uint64_t __addr = (uint64_t)addr;
	uint64_t __len = (uint64_t)len;

	return (int)__libfingc_syscall_2(__addr, __len, 11);
}

static inline void *__brk(unsigned long addr)
{
	uint64_t __addr = (uint64_t)addr;

	return (void *)__libfingc_syscall_1(__addr, 12);
}

static inline void *__mremap(void *old_address, size_t old_size, size_t new_size,
			     int flags, void *new_address)
{
	uint64_t __old_address = (uint64_t)old_address;
	uint64_t __old_size = (uint64_t)old_size;
	uint64_t __new_size = (uint64_t)new_size;
	uint64_t __flags = (uint64_t)flags;
	uint64_t __new_address = (uint64_t)new_address;

	return (void *)__libfingc_syscall_5(__old_address, __old_size, __new_size,
					    __flags, __new_address, 25);
}

#endif /* _LIBFINGC_SYSCALL_H_ */