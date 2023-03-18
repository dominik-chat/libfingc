/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stddef.h>
#include "syscall.h"
#include "arch_al.h"

#define PAGE_SIZE	4096

#define PROT_READ	0x01
#define PROT_WRITE	0x02

#define MAP_PRIVATE	0x02
#define MAP_ANONYMOUS	0x20

#define MREMAP_MAYMOVE	0x01

extern uintptr_t __libfingc_heap_start;
extern uintptr_t __libfingc_heap_end;

void *__libfingc_arch_al_mmap(size_t size)
{
	if (size == 0) {
		return (void *)-1;
	}

	return __mmap(NULL, size, (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
}

int __libfingc_arch_al_munmap(void *addr, size_t size)
{
	if ((size == 0)  || (addr == NULL)) {
		return -1;
	}

	return __munmap(addr, size);
}

void *__libfingc_arch_al_mremap(void *old_address, size_t old_size, size_t new_size)
{
	if ((old_address == NULL) || (old_size == 0) || (new_size == 0)) {
		return (void *)-1;
	}

	if (((uintptr_t)old_address && (PAGE_SIZE - 1)) != 0) {
		return (void *)-1;
	}

	return __mremap(old_address, old_size, new_size, MREMAP_MAYMOVE, NULL);
}

int __libfingc_arch_al_sbrk(intptr_t offset)
{
	uintptr_t cur = __libfingc_heap_end;
	uintptr_t next;
	void *ret;

	if (offset == 0) {
		return 0;
	}

	if (offset < 0) {
		next = cur - ((uintptr_t)-offset);
	}

	if (offset > 0) {
		next = cur + ((uintptr_t)offset);
	}

	ret = __brk(next);
	if (ret == (void *)-1) {
		return -1;
	}

	__libfingc_heap_end = next;

	return 0;
}

int __libfingc_arch_al_init_heap(void)
{
	__libfingc_heap_start = (uintptr_t)__brk(0);
	if (__libfingc_heap_start == 0) {
		return -1;
	}
	__libfingc_heap_end = __libfingc_heap_start;

	return 0;
}