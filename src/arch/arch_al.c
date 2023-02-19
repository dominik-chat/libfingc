/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stddef.h>
#include "syscall.h"
#include "arch_al.h"

extern void *__libfingc_heap_start;
extern void *__libfingc_heap_end;

int __libfingc_arch_al_init_heap(void)
{
	__libfingc_heap_start = brk(0);
	if (__libfingc_heap_start == NULL) {
		return 1;
	}
	__libfingc_heap_end = __libfingc_heap_start;

	return 0;
}