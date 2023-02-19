/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _STDLIB_H
#define _STDLIB_H	1

#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

#define RAND_MAX 32767

int rand(void);

void srand(unsigned int seed);

void *aligned_alloc(size_t alignment, size_t size)
	__attribute__((malloc, alloc_size(2), alloc_align(1))) __attribute__((warn_unused_result));

void *calloc(size_t nmemb, size_t size)
	__attribute__((malloc, alloc_size(1, 2))) __attribute__((warn_unused_result));

void free(void *ptr);

void *malloc(size_t size)
	__attribute__((malloc, alloc_size(1))) __attribute__((warn_unused_result));

void *realloc(void *ptr, size_t size)
	__attribute__((alloc_size(2))) __attribute__((warn_unused_result));

#endif /* _STDLIB_H */