/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jat/jat.h"

extern JAT_TESTS_DEF(tests_string);
extern JAT_TESTS_DEF(tests_stdlib);

extern int __libfingc_arch_al_init_heap(void);

int main()
{
	int ret;

	__libfingc_arch_al_init_heap();

	ret = jat_run(tests_stdlib, "stdlib.h");
	if (ret) {
		return ret;
	}
	return jat_run(tests_string, "string.h");
}