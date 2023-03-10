/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stddef.h>
#include "syscall.h"
#include "arch_al.h"

#define PROT_READ	0x1
#define PROT_WRITE	0x2

#define MAP_PRIVATE	0x02

#define MAP_ANONYMOUS	0x20

extern const uintptr_t __libfingc_heap_start;
extern uintptr_t __libfingc_heap_end;

void *__libfingc_arch_al_mmap(size_t size)
{
	if (size == 0) {
		return NULL;
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
	uintptr_t *tmp = (uintptr_t *)&__libfingc_heap_start;

	*tmp = (uintptr_t)__brk(0);
	if (__libfingc_heap_start == 0) {
		return -1;
	}
	__libfingc_heap_end = __libfingc_heap_start;

	return 0;
}