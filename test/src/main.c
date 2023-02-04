/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <string.h>
#include "string_test.h"
#include "jat.h"

static int ut_memset(void)
{
	JAT_TEST_BEGINNING;

	unsigned char mem1[10];
	unsigned char mem2[10];
	unsigned char mem3[10];

	memset(mem2, 0, sizeof(mem2));
	memset(mem3, 1, sizeof(mem3));

	JAT_ASSERT(test_memset(mem1, 0, sizeof(mem1)) == mem1);
	JAT_ASSERT(memcmp(mem1, mem2, sizeof(mem1)) == 0);

	JAT_ASSERT(test_memset(mem1, 1, sizeof(mem1)) == mem1);
	JAT_ASSERT(memcmp(mem1, mem2, sizeof(mem1)) != 0);
	JAT_ASSERT(memcmp(mem1, mem3, sizeof(mem1)) == 0);

	JAT_ASSERT(test_memset(mem1, 0x101, sizeof(mem1)) == mem1);
	JAT_ASSERT(memcmp(mem1, mem2, sizeof(mem1)) != 0);
	JAT_ASSERT(memcmp(mem1, mem3, sizeof(mem1)) == 0);

	JAT_TEST_ENDING;
}

static int ut_memcpy(void)
{
	JAT_TEST_BEGINNING;

	JAT_TEST_ENDING;
}

static int ut_memmove(void)
{
	JAT_TEST_BEGINNING;
	JAT_TEST_ENDING;
}

static int ut_memcmp(void)
{
	JAT_TEST_BEGINNING;

	unsigned char mem1[10];
	unsigned char mem2[20];
	unsigned char mem3[20];

	memset(mem1, 0, sizeof(mem1));
	memset(mem2, 0, sizeof(mem2));
	memset(mem3, 1, sizeof(mem3));

	JAT_ASSERT(test_memcmp(mem1, mem2, sizeof(mem1)) == 0);
	JAT_ASSERT(test_memcmp(mem2, mem3, sizeof(mem2)) != 0);
	JAT_ASSERT(test_memcmp(mem1, mem3, sizeof(mem1)) != 0);

	mem1[0] = 1;
	JAT_ASSERT(test_memcmp(mem1, mem2, sizeof(mem1)) != 0);
	JAT_ASSERT(test_memcmp(mem1, mem3, 1) == 0);

	JAT_TEST_ENDING;
}

static int ut_memchr(void)
{
	JAT_TEST_BEGINNING;
	JAT_TEST_ENDING;
}

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
	JAT_TEST(ut_memset, "memset"),
	JAT_TEST(ut_memcpy, "memcpy"),
	JAT_TEST(ut_memmove, "memmove"),
	JAT_TEST(ut_memcmp, "memcmp"),
	JAT_TEST(ut_memchr, "memchr"),

	JAT_TEST(ut_strcmp, "strcmp")
);

int main()
{
	return jat_run(tests_string);
}