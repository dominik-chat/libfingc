/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _LIBFINGC_ARCH_AL_H_
#define _LIBFINGC_ARCH_AL_H_

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Mmap like function.
 *
 * This function should behave similar to linux mmap.
 * This function should map a memory block with read and write flags. 
 *
 * @param size Size of block to map.
 *
 * @retval Pointer to allocated block on success.
 * @retval (void *)-1 on error
 */
void *__libfingc_arch_al_mmap(size_t size);

/**
 * @brief Munmap like function.
 *
 * This function should behave similar to linux munmap.
 * This function should unmap a previously mapped memory block. 
 *
 * @param addr Address to unmap.
 * @param size Size of block to unmap.
 *
 * @retval 0 Success.
 * @retval Negative on error
 */
int __libfingc_arch_al_munmap(void *addr, size_t size);

/**
 * @brief Mremap like function.
 *
 * This function should behave similar to linux mremap.
 * This function should remap a memory block to a new specified size.
 * If any of the size is zero or address is NULL the function will fail.
 * The address should be page-aligned. 
 *
 * @param old_size Original size of block to remap.
 * @param new_size Requested size of block to remap.
 *
 * @retval Pointer to remapped block on success.
 * @retval (void *)-1 on error
 */
void *__libfingc_arch_al_mremap(void *old_address, size_t old_size, size_t new_size);

/**
 * @brief Sbrk like function.
 *
 * This function should behave similar to linux sbrk.
 * When the offset is positive the break should be moved forward.
 * When the offset is negative the break should be moved back.
 * In case of 0 offset the function does nothing.
 *
 * @param offset Offset to move program break.
 *
 * @retval 0 Success.
 * @retval Negative on error
 */
int __libfingc_arch_al_sbrk(intptr_t offset);

/**
 * @brief Initialize heap.
 *
 * This function initializes heap local data.
 *
 * @retval 0 Success.
 * @retval Negative on error
 */
int __libfingc_arch_al_init_heap(void);

#endif /* _LIBFINGC_ARCH_AL_H_ */