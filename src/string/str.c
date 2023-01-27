/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "string.h"

char *strchr(const char *s, int c)
{
	char _c = (char)c;
	size_t len;
	size_t i;

	len = strlen(s);

	if (_c == '\0') {
		return (char *)&s[len];
	}

	for (i = 0; i < len; i++) {
		if (s[i] == _c) {
			return (char *)&s[i];
		}
	}

	return NULL;
}

size_t strlen(const char *s)
{
	size_t i = 0;

	while (s[i] != '\0') {
		i++;
	}

	return i;
}

size_t strcspn(const char *s1, const char *s2)
{
	size_t s2_len;
	size_t i = 0;

	s2_len = strlen(s2);
	if (s2_len == 0) {
		return strlen(s1);
	}

	while (s1[i] != '\0') {
		if (memchr(s2, s1[i], s2_len) != NULL) {
			return i;
		}
		i++;
	}

	return i;
}

char *strpbrk(const char *s1, const char *s2)
{
	size_t s2_len;
	size_t i = 0;

	s2_len = strlen(s2);
	if (s2_len == 0) {
		return NULL;
	}

	while (s1[i] != '\0') {
		if (memchr(s2, s1[i], s2_len) != NULL) {
			return (char *)&s1[i];
		}
		i++;
	}

	return NULL;
}

char *strrchr(const char *s, int c)
{
	char _c = (char)c;
	size_t i = 0;

	while (s[i] != '\0') {
		if (s[i] == _c) {
			return (char *)&s[i];
		}
		i++;
	}

	return NULL;
}

size_t strspn(const char *s1, const char *s2)
{
	size_t s2_len;
	size_t i = 0;

	s2_len = strlen(s2);
	if (s2_len == 0) {
		return strlen(s1);
	}

	while (s1[i] != '\0') {
		if (memchr(s2, s1[i], s2_len) == NULL) {
			return i;
		}
		i++;
	}

	return i;
}

char *strstr(const char *s1, const char *s2)
{
	size_t i = 0;
	size_t j = 0;

	while (s1[i] != '\0') {
		if (s1[i] == s2[j]) {
			j++;
		} else {
			j = 0;
		}

		if (s2[j] == '\0') {
			return (char *)&s1[i-j];
		}

		i++;
	}

	return NULL;
}

char *strtok(char * restrict s1, const char * restrict s2)
{
	static char *buf;
	char *tmpc;
	size_t tmpi;

	if (s1 != NULL) {
		buf = s1;
	}

	tmpc = strpbrk(buf, s2);
	if (tmpc == NULL) {
		return NULL;
	}
	*buf = '\0';
	buf++;

	tmpi = strspn(buf, s2);
	return &buf[tmpi];
}

char *strerror(int errnum)
{
	(void)errnum;
	return "Sorry strerror, not yet supported";
}

int strcoll(const char *s1, const char *s2)
{
	(void)s1;
	(void)s2;
	return 0;
}

size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n)
{
	(void)s1;
	(void)s2;
	(void)n;
	return 0;
}