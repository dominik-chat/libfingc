#
# Copyright 2023 Dominik Chat
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

.section .text

.global _start
_start:
	xorq %rbp, %rbp
	popq %rdi
	lea 8(%rsp, %rdi, 8), %rdx
	movq %rsp, %rbp
	movq %rsp, %rsi

	pushq %rdx
	pushq %rsi
	pushq %rdi

	call __libfingc_init # (int argc, char* argv[], char* envp[])

	#call _init

	popq %rdi
	popq %rsi
	popq %rdx

	call main # (int argc, char* argv[], char* envp[])

	movslq %edi, %rdi
	pushq %rdi

	#call _fini

	popq %rdi
	movq $60, %rax
	syscall
