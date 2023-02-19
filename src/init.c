/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "arch/arch_al.h"

void __libfingc_init(int argc, char* argv[], char* envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	__libfingc_arch_al_init_heap();
}
