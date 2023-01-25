/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "string.h"

int strcmp(const char *s1, const char *s2)
{
	size_t i = 0;

	while ((s1[i] != s2[i]) && (s1[i] != '\0') && (s2[i] != '\0')) {
		i++;
	}

	return ((int)s1[i] - (int)s2[i]);
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	if (n == 0) {
		return 0;
	}

	while ((s1[i] != s2[i]) && (i < n) && (s1[i] != '\0') && (s2[i] != '\0')) {
		i++;
	}

	return ((int)s1[i] - (int)s2[i]);
}