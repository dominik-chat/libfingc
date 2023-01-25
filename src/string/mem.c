/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "string.h"

void *memchr(const void *s, int c, size_t n)
{
	const unsigned char _c = (const unsigned char)c;
	const unsigned char *_s = (const unsigned char *)s;
	size_t i;

	for (i = 0; i < n; i++) {
		if (_s[i] == _c) {
			return (void *)&_s[i];
		}
	}

	return NULL;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *_s1 = (const unsigned char *)s1;
	const unsigned char *_s2 = (const unsigned char *)s2;
	size_t i;

	for (i = 0; i < n; i++) {
		if (_s1[i] != _s2[i]) {
			return ((int)_s1[i] - (int)_s2[i]);
		}
	}

	return 0;
}

void *memcpy(void * restrict s1, const void * restrict s2, size_t n)
{
	unsigned char *_s1 = (unsigned char *)s1;
	const unsigned char *_s2 = (const unsigned char *)s2;
	size_t i;

	for (i = 0; i < n; i++) {
		_s1[i] = _s2[i];
	}

	return s1;
}

void *memmove(void *s1, const void *s2, size_t n)
{
	unsigned long int s1_adr = (unsigned long int)s1;
	unsigned long int s2_adr = (unsigned long int)s2;
	unsigned char *_s1 = (unsigned char *)s1;
	const unsigned char *_s2 = (const unsigned char *)s2;
	size_t i;

	if (n == 0) {
		return s1;
	}

	/* Beggining first */
	if (s2_adr >= s1_adr) {
		for (i = 0; i < n; i++) {
			_s1[i] = _s2[i];
		}
	} else { /* End first */
		for (i = n; i > 0; i--) {
			_s1[i - 1] = _s2[i - 1];
		}
	}

	return s1;
}

void *memset(void *s, int c, size_t n)
{
	unsigned char *_s = (unsigned char *)s;
	unsigned char _c = (unsigned char)c;
	size_t i;

	for (i = 0; i < n; i++) {
		_s[i] = _c;
	}

	return s;
}