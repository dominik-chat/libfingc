/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdlib.h>

static unsigned long int __seed = 1;

int rand(void)
{
	__seed = __seed * 1103515245 + 12345;
	return (unsigned int)(__seed / 65536) % RAND_MAX;
}

void srand(unsigned int seed)
{
	__seed = seed;
}