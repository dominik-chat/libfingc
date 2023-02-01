/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jat.h"

extern int test_strcmp(const char *s1, const char *s2);

static int ut_strcmp(void)
{
	JAT_TEST_BEGINNING;

	char str1[] = "abcdefghijkl";
	char str2[] = "abcdefg";
	char str3[] = "";

	JAT_ASSERT(test_strcmp(str1, str1) == 0);
	JAT_ASSERT(test_strcmp(str2, str2) == 0);
	JAT_ASSERT(test_strcmp(str3, str3) == 0);

	JAT_ASSERT(test_strcmp(str1, str2) > 0);
	JAT_ASSERT(test_strcmp(str2, str3) > 0);

	JAT_ASSERT(test_strcmp(str2, str1) < 0);
	JAT_ASSERT(test_strcmp(str3, str2) < 0);

	JAT_TEST_ENDING;
}

static JAT_TESTS(tests_string,
	JAT_TEST(ut_strcmp, "strcmp")
);

int main()
{
	return jat_run(tests_string);
}