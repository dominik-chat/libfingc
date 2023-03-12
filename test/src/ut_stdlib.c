/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include "jat/jat.h"

#include "stdlib_test.h"

static int ut_malloc(void)
{
	JAT_TEST_BEGINNING;

	unsigned char *tmp;
	unsigned char *tmp2;

	tmp = test_malloc(sizeof(*tmp));
	tmp = test_malloc(sizeof(*tmp));
	tmp = test_malloc(sizeof(*tmp));
	JAT_ASSERT(tmp != NULL);
	printf("Address %p\n", tmp);
	test_free(tmp);

	tmp = test_malloc(sizeof(*tmp));
	JAT_ASSERT(tmp != NULL);
	printf("Address %p\n", tmp);

	test_malloc(sizeof(*tmp));
	tmp2 = test_malloc(sizeof(*tmp));
	JAT_ASSERT(tmp != NULL);
	printf("Address %p\n", tmp2);
	test_free(tmp);

	tmp = test_malloc(sizeof(*tmp));
	JAT_ASSERT(tmp != NULL);
	printf("Address %p\n", tmp);
	test_free(tmp);

	JAT_TEST_ENDING;
}

JAT_TESTS(tests_stdlib,
	JAT_TEST(ut_malloc, "malloc")
);