/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

__attribute__((aligned(4096))) unsigned char heap[16384];

extern uintptr_t __libfingc_heap_start;
extern uintptr_t __libfingc_heap_end;

void *__libfingc_arch_al_mmap(size_t size)
{
	(void)size;
	return NULL;
}

int __libfingc_arch_al_munmap(void *addr, size_t size)
{
	(void)addr;
	(void)size;
	return -1;
}

int __libfingc_arch_al_sbrk(intptr_t offset)
{
	uintptr_t next;

	if (offset == 0) {
		return 0;
	}

	if (offset < 0) {
		next = __libfingc_heap_end - ((uintptr_t)-offset);
	}

	if (offset > 0) {
		next = __libfingc_heap_end + ((uintptr_t)offset);
	}

	if (((next - __libfingc_heap_start) > sizeof(heap)) || (next < __libfingc_heap_start)) {
		return -1;
	}

	__libfingc_heap_end = next;
	return 0;
}

int __libfingc_arch_al_init_heap(void)
{
	__libfingc_heap_start = (uintptr_t)heap;
	__libfingc_heap_end = __libfingc_heap_start;
	return 0;
}