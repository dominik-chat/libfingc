/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <string.h>
#include <stdlib.h>
#include "jat.h"

#include "string_test.h"

static int ut_memset(void)
{
	JAT_TEST_BEGINNING;

	unsigned char mem1[10];
	unsigned char mem2[10];
	unsigned char mem3[10];
	void *ret;

	memset(mem2, 0, sizeof(mem2));
	memset(mem3, 1, sizeof(mem3));

	ret = test_memset(mem1, 0, sizeof(mem1));
	JAT_ASSERT(memcmp(mem1, mem2, sizeof(mem1)) == 0);
	JAT_ASSERT(ret == mem1);

	ret = test_memset(mem1, 1, sizeof(mem1));
	JAT_ASSERT(memcmp(mem1, mem2, sizeof(mem1)) != 0);
	JAT_ASSERT(memcmp(mem1, mem3, sizeof(mem1)) == 0);
	JAT_ASSERT(ret == mem1);

	ret = test_memset(mem1, 0x101, sizeof(mem1));
	JAT_ASSERT(memcmp(mem1, mem2, sizeof(mem1)) != 0);
	JAT_ASSERT(memcmp(mem1, mem3, sizeof(mem1)) == 0);
	JAT_ASSERT(ret == mem1);

	JAT_TEST_ENDING;
}

static int ut_memcpy(void)
{
	JAT_TEST_BEGINNING;

	unsigned char mem1[10];
	unsigned char mem2[100];
	unsigned char mem3[256];
	unsigned char mem4[256];
	void *ret;
	size_t i;

	srand(1);

	for (i = 0; i < sizeof(mem1); i++) {
		mem1[i] = (unsigned char)rand();
	}
	for (i = 0; i < sizeof(mem2); i++) {
		mem2[i] = (unsigned char)rand();
	}
	for (i = 0; i < sizeof(mem3); i++) {
		mem3[i] = (unsigned char)rand();
	}

	ret = test_memcpy(mem4, mem1, sizeof(mem1));
	JAT_ASSERT(memcmp(mem4, mem1, sizeof(mem1)) == 0);
	JAT_ASSERT(ret == mem4);

	ret = test_memcpy(mem4, mem2, sizeof(mem2));
	JAT_ASSERT(memcmp(mem4, mem2, sizeof(mem2)) == 0);
	JAT_ASSERT(ret == mem4);

	ret = test_memcpy(mem4, mem3, sizeof(mem3));
	JAT_ASSERT(memcmp(mem4, mem3, sizeof(mem3)) == 0);
	JAT_ASSERT(ret == mem4);

	ret = test_memcpy(mem4, mem1, 0);
	JAT_ASSERT(memcmp(mem4, mem3, sizeof(mem3)) == 0);
	JAT_ASSERT(ret == mem4);

	ret = test_memcpy(mem4, mem2, 0);
	JAT_ASSERT(memcmp(mem4, mem3, sizeof(mem3)) == 0);
	JAT_ASSERT(ret == mem4);

	JAT_TEST_ENDING;
}

static int ut_memmove(void)
{
	JAT_TEST_BEGINNING;

	unsigned char mem1[10] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	unsigned char mem2[10] = {
		0, 1, 2, 5, 6, 7, 8, 9, 8, 9
	};
	unsigned char mem3[10] = {
		0, 1, 2, 5, 2, 5, 6, 7, 8, 9
	};
	void *ret;

	ret = test_memmove(&mem1[3], &mem1[5], 5);
	JAT_ASSERT(memcmp(mem1, mem2, sizeof(mem1)) == 0);
	JAT_ASSERT(ret == &mem1[3]);

	ret = test_memmove(&mem1[4], &mem1[2], 5);
	JAT_ASSERT(memcmp(mem1, mem3, sizeof(mem1)) == 0);
	JAT_ASSERT(ret == &mem1[4]);

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

	unsigned char *ptr;
	unsigned char mem[10] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	ptr = test_memchr(mem, 0, sizeof(mem));
	JAT_ASSERT(*ptr == 0);

	ptr = test_memchr(mem, 2, sizeof(mem));
	JAT_ASSERT(*ptr == 2);

	ptr = test_memchr(mem, 6, sizeof(mem));
	JAT_ASSERT(*ptr == 6);

	ptr = test_memchr(mem, 8, 7);
	JAT_ASSERT(ptr == NULL);

	ptr = test_memchr(mem, 10, sizeof(mem));
	JAT_ASSERT(ptr == NULL);

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