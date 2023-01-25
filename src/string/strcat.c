/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "string.h"

char *strcat(char * restrict s1, const char * restrict s2)
{
	size_t offset;
	size_t i = 0;

	offset = strlen(s1);

	while (s2[i] != '\0') {
		s1[offset + i] = s2[i];
		i++;
	}
	s1[offset + i] = s2[i];

	return s1;
}

char *strncat(char * restrict s1, const char * restrict s2, size_t n)
{
	size_t offset;
	size_t i = 0;

	if (n == 0) {
		return s1;
	}

	offset = strlen(s1);

	while ((s2[i] != '\0') && (i < n)) {
		s1[offset + i] = s2[i];
		i++;
	}

	if (i < n) {
		s1[offset + i] = s2[i];
	}

	return s1;
}