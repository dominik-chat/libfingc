#
# Copyright 2023 Dominik Chat
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

.section .text

.global _start
_start:
	xorq %rbp, %rbp
	pushq %rbp
	pushq %rbp
	movq %rsp, %rbp

	pushq %rsi
	pushq %rdi

	#call __libfingc_init(int argc, char* argv[], int envc, char* envp[])

	#call _init

	popq %rdi
	popq %rsi

	movq main, %rax
	call *(%rax) # main(int argc, char* argv[])

	movslq %edi, %rdi
	pushq %rdi

	#call _fini

	popq %rdi
	movq $60, %rax
	syscall
