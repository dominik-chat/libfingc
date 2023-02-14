/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jat/jat.h"

extern JAT_TESTS_DEF(tests_string);

int main()
{
	return jat_run(tests_string, "string.h");
}