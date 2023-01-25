/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "string.h"

char *strcpy(char * restrict s1, const char * restrict s2)
{
	size_t i = 0;

	while (s2[i] != '\0') {
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];

	return s1;
}

char *strncpy(char * restrict s1, const char * restrict s2, size_t n)
{
	size_t i = 0;

	while ((s2[i] != '\0') && (i < n)) {
		s1[i] = s2[i];
		i++;
	}

	if (i == n) {
		return s1;
	}

	for (; i < n; i++) {
		s1[i] = '\0';
	}

	return s1;
}