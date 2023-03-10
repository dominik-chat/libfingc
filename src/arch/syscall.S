#
# Copyright 2023 Dominik Chat
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

.section .text

.global __libfingc_syscall_0
__libfingc_syscall_0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, %rax
	syscall
	popq	%rbp
	ret

.global __libfingc_syscall_1
__libfingc_syscall_1:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rsi, %rax
	syscall
	popq	%rbp
	ret

.global __libfingc_syscall_2
__libfingc_syscall_2:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdx, %rax
	syscall
	popq	%rbp
	ret

.global __libfingc_syscall_3
__libfingc_syscall_3:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rcx, %rax
	syscall
	popq	%rbp
	ret

.global __libfingc_syscall_4
__libfingc_syscall_4:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rcx, %r10
	movq	%r8, %rax
	syscall
	popq	%rbp
	ret

.global __libfingc_syscall_5
__libfingc_syscall_5:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rcx, %r10
	movq	%r9, %rax
	syscall
	popq	%rbp
	ret

.global __libfingc_syscall_6
__libfingc_syscall_6:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rcx, %r10
	movq	16(%rbp), %rax
	syscall
	popq	%rbp
	ret