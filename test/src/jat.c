/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <stdarg.h>

/* Just A Tester */
#include "jat.h"

enum jat_color {
	COLOR_RED,
	COLOR_GREEN,
	COLOR_WHITE,
};

static void printf_col(const enum jat_color col, const char *format, ...)
{
	va_list arg;
	va_start(arg, format);

	switch (col) {
		case COLOR_RED:
		printf("\e[31m");
		break;

		case COLOR_GREEN:
		printf("\e[32m");
		break;

		case COLOR_WHITE:

		default:
		printf("\e[37m");
		break;
	}

	vprintf(format, arg);
	printf("\e[37m");
	va_end(arg);
}

void jat_report(const char *file, const int line, const char *func, const char *cond_str, const bool cond)
{
	if (cond == true) {
		return;
	}

	printf_col(COLOR_RED, "Assertion \"%s\" in %s failed at %s:%d\n", cond_str, func, file, line);
}

int jat_run(const struct jat_test *tests)
{
	int tmp;
	size_t i = 0;
	int failed = 0;

	if (tests == NULL) {
		printf_col(COLOR_RED, "Woah, please pass non-NULL pointer pls.\n");
		return -1;
	}

	while (tests[i].name != NULL) {
		printf_col(COLOR_WHITE, "Running test %s...\n", tests[i].name);
		tmp = tests[i].func();

		if (tmp > 0) {
			failed++;
			printf_col(COLOR_RED, "%i checks failed for test %s.\n", tmp, tests[i].name);
		} else {
			printf_col(COLOR_GREEN, "%s test completed successfully.\n", tests[i].name);
		}
		i++;
	}

	printf("Total tests failed %i\n", failed);
	return failed;
}