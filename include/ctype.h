/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _CTYPE_H
#define _CTYPE_H	1

int isalnum(int c)
	__attribute__((warn_unused_result));

int isalpha(int c)
	__attribute__((warn_unused_result));

int isblank(int c)
	__attribute__((warn_unused_result));

int iscntrl(int c)
	__attribute__((warn_unused_result));

int isdigit(int c)
	__attribute__((warn_unused_result));

int isgraph(int c)
	__attribute__((warn_unused_result));

int islower(int c)
	__attribute__((warn_unused_result));

int isprint(int c)
	__attribute__((warn_unused_result));

int ispunct(int c)
	__attribute__((warn_unused_result));

int isspace(int c)
	__attribute__((warn_unused_result));

int isupper(int c)
	__attribute__((warn_unused_result));

int isxdigit(int c)
	__attribute__((warn_unused_result));

int tolower(int c)
	__attribute__((warn_unused_result));

int toupper(int c)
	__attribute__((warn_unused_result));


#endif /* _CTYPE_H */