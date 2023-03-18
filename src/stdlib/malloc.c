/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdalign.h>
#include "string.h"
#include "../arch/arch_al.h"

#ifndef __SIZE_WIDTH__
#warning __SIZE_WIDTH__ not defined
#endif

/* TODO: Replace by architecture specific config file */
#define BIG_ALLOC_SIZE			16384

#define HEADER_SIZE			(offsetof(struct small_header, mem))
#define DIV_UP(dividend, divisor)	(((dividend)+(divisor))/(divisor))
#define TOTAL_SIZE(size)		(DIV_UP((HEADER_SIZE + size), alignof(max_align_t)) * \
									alignof(max_align_t))

uintptr_t __libfingc_heap_start;
uintptr_t __libfingc_heap_end;

struct small_header {
	struct small_header *prev;
	size_t size	: (__SIZE_WIDTH__-1);
	size_t free	: 1;
	max_align_t mem[];
};

struct big_block {
	struct big_block *next;
	size_t size;
	void *data;
};

static struct big_block *big_blocks = NULL;

static void *small_create_block(void *addr, struct small_header *prev, size_t size)
{
	struct small_header *block = (struct small_header *)addr;

	block->prev = prev;
	block->size = size;
	block->free = 0;

	return (void *)block->mem;
}

static void *small_divide_block(struct small_header *block, size_t size)
{
	/* ...-block-new-next-...*/
	struct small_header *next;
	struct small_header *new;
	size_t rem_size = block->size - size;

	next = (struct small_header *)((uintptr_t)block + block->size);
	new = (struct small_header *)((uintptr_t)block + size);

	/* Not possible to divide, allocate more memory than necessary */
	if (rem_size < HEADER_SIZE) {
		block->free = 0;
		return (void *)block->mem;
	}

	next->prev = new;

	new->prev = block;
	new->size = rem_size;
	new->free = 1;

	block->size = size;
	block->free = 1;

	return (void *)block->mem;
}

static void small_merge_block(struct small_header *block)
{
	/* Try to merge block and next block and previous block as free */
	struct small_header *next;
	struct small_header *prev = block->prev;
	struct small_header *new;

	next = (struct small_header *)((uintptr_t)block + block->size);

	/* This is the only block, no previous or next block to merge */
	if ((prev == NULL) && ((uintptr_t)next == __libfingc_heap_end)) {
		block->free = 1;
		return;
	}

	new = block;
	if (prev != NULL) {
		if (prev->free == 1) {
			new = prev;
			new->size = new->size + block->size;
		}
	}

	if ((uintptr_t)next != __libfingc_heap_end) {
		if (next->free == 1) {
			new->size = new->size + next->size;
		}
	}

	new->free = 1;
}

static uintptr_t small_search_free(size_t total_size, struct small_header **prev)
{
	uintptr_t cur = __libfingc_heap_start;
	struct small_header *block;

	*prev = NULL;

	while (cur < __libfingc_heap_end) {
		block = (struct small_header *)cur;

		if ((block->size >= total_size) && (block->free == 1)){
			return cur;
		}

		*prev = block;
		cur = cur + block->size;
	}

	return __libfingc_heap_end;
}

static void *small_alloc_end(size_t total_size, struct small_header *prev)
{
	uintptr_t old_end = __libfingc_heap_end;
	int ret;

	ret = __libfingc_arch_al_sbrk(total_size);
	if (ret < 0) {
		return NULL;
	}

	return small_create_block((void *)old_end, prev, total_size);
}

static void *small_alloc(size_t size)
{
	size_t total_size = TOTAL_SIZE(size);
	size_t aval_size = __libfingc_heap_end - __libfingc_heap_start;
	struct small_header *prev;
	uintptr_t block;

	/* No heap allocated */
	if (aval_size == 0) {
		return small_alloc_end(total_size, NULL);
	}

	block = small_search_free(total_size, &prev);
	if (block == __libfingc_heap_end) {
		return small_alloc_end(total_size, prev);
	}

	return small_divide_block((struct small_header *)block, total_size);
}

static void small_dealloc(void *ptr)
{
	struct small_header *block;

	block = (struct small_header *)(((char *)ptr)-HEADER_SIZE);
	small_merge_block(block);
	/* TODO: Should brk be moved if there is free space ? */
}

static void *big_alloc(size_t size)
{
	struct big_block *block;
	struct big_block *tmp;

	block = malloc(sizeof(*block));
	if (block == NULL) {
		return NULL;
	}

	block->next = NULL;
	block->size = size;
	block->data = __libfingc_arch_al_mmap(size);

	if (block->data == (void *)-1) {
		free(block);
		return NULL;
	}

	if (big_blocks == NULL) {
		big_blocks = block;
	} else {
		tmp = big_blocks;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = block;
	}

	return block->data;
}

void big_dealloc(void *ptr)
{
	struct big_block *block = big_blocks;
	struct big_block *prev = NULL;
	int ret;

	if (block == NULL) {
		return;
	}

	while (block->data != ptr) {
		prev = block;
		block = block->next;
		if (block == NULL) {
			return;
		}
	}

	ret = __libfingc_arch_al_munmap(block->data, block->size);
	/* FIXME: Use this return value */
	(void)ret;

	if (prev == NULL) {
		big_blocks = block->next;
	} else {
		prev->next = block->next;
	}

	free(block);
}

void *aligned_alloc(size_t alignment, size_t size)
{
	/* TODO: Check if alignment is multiple of 2 */

	if (alignment < alignof(max_align_t)) {
		return malloc(size);
	} else {
		/* TODO: some block alignment mechanism */
		return NULL;
	}
}

void *calloc(size_t nmemb, size_t size)
{
	size_t total_size = size * nmemb;
	void *ret;

	ret = malloc(total_size);
	if (ret != NULL) {
		memset(ret, 0, total_size);
	}

	return ret;
}

void free(void *ptr)
{
	if (((uintptr_t)ptr > __libfingc_heap_start) && ((uintptr_t)ptr < __libfingc_heap_end)) {
		small_dealloc(ptr);
	} else {
		big_dealloc(ptr);
	}
}

void *malloc(size_t size)
{
	if (size == 0) {
		return NULL;
	} else if (size >= BIG_ALLOC_SIZE) {
		return big_alloc(size);
	} else {
		return small_alloc(size);
	}
}

void *realloc(void *ptr, size_t size)
{

}