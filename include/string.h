/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _STRING_H
#define _STRING_H	1

#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

void *memcpy(void * restrict s1, const void * restrict s2, size_t n)
	__attribute__((nonnull(1, 2)));

void *memmove(void *s1, const void *s2, size_t n)
	__attribute__((nonnull(1, 2)));

char *strcpy(char * restrict s1, const char * restrict s2)
	__attribute__((nonnull(1, 2)));

char *strncpy(char * restrict s1, const char * restrict s2, size_t n)
	__attribute__((nonnull(1, 2)));

char *strcat(char * restrict s1, const char * restrict s2)
	__attribute__((nonnull(1, 2)));

char *strncat(char * restrict s1, const char * restrict s2, size_t n)
	__attribute__((nonnull(1, 2)));

int memcmp(const void *s1, const void *s2, size_t n)
	__attribute__((nonnull(1, 2))) __attribute__ ((pure));

int strcmp(const char *s1, const char *s2)
	__attribute__((nonnull(1, 2))) __attribute__ ((pure));

int strncmp(const char *s1, const char *s2, size_t n)
	__attribute__((nonnull(1, 2))) __attribute__ ((pure));

void *memchr(const void *s, int c, size_t n)
	__attribute__((nonnull(1))) __attribute__ ((pure));

char *strchr(const char *s, int c)
	__attribute__((nonnull(1))) __attribute__ ((pure));

size_t strcspn(const char *s1, const char *s2)
	__attribute__((nonnull(1, 2))) __attribute__ ((pure));

char *strpbrk(const char *s1, const char *s2)
	__attribute__((nonnull(1, 2))) __attribute__ ((pure));

char *strrchr(const char *s, int c)
	__attribute__((nonnull(1))) __attribute__ ((pure));

size_t strspn(const char *s1, const char *s2)
	__attribute__((nonnull(1, 2))) __attribute__ ((pure));

char *strstr(const char *s1, const char *s2)
	__attribute__((nonnull(1, 2))) __attribute__ ((pure));

char *strtok(char * restrict s1, const char * restrict s2)
	__attribute__((nonnull(2)));

void *memset(void *s, int c, size_t n)
	__attribute__((nonnull(1)));

char *strerror(int errnum)
	__attribute__ ((pure));

size_t strlen(const char *s)
	__attribute__((nonnull(1))) __attribute__ ((pure));


/* This will *NOT* be supported - too much complexity */
int strcoll(const char *s1, const char *s2)
	__attribute__((error("strcoll is not implemented")));
size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n)
	__attribute__((error("strxfrm is not implemented")));

#endif /* _STRING_H */