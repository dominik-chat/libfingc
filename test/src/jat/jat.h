/*
 * Copyright 2023 Dominik Chat
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _JAT_H_
#define _JAT_H_

#include <stddef.h>
#include <stdbool.h>

#define JAT_TEST(_func, _name) {.func = _func, .name = _name}
#define JAT_TESTS(_name, ...)	\
struct jat_test _name[] = {	\
	__VA_ARGS__,		\
	JAT_TEST(NULL, NULL)	\
}

#define JAT_TESTS_DEF(_name) struct jat_test _name[]

#define JAT_ASSERT(_cond)						\
	jat_report(__FILE__, __LINE__, __FUNCTION__, #_cond, (_cond));	\
	if ((_cond) == false) __cnt++

#define JAT_TEST_BEGINNING int __cnt = 0
#define JAT_TEST_ENDING return __cnt

/**
 * @typedef jat_test_func
 * @brief Single unit test function.
 *
 * @retval Number of failed checks.
 */
typedef int (*jat_test_func)(void);

/**
 * @brief Single unit test structure.
 */
struct jat_test {
	jat_test_func func;
	char *name;
};

/**
 * @brief Report test error if necessary. This function should be considered private.
 */
void jat_report(const char *file, const int line, const char *func, const char *cond_str, const bool cond);

/**
 * @brief Start tests.
 *
 * Start unit tests specified by pointer.
 *
 * @param tests Pointer unit test structure. Last element contents should be NULL.
 * @param name Name of the test group. Can be NULL for no name.
 * 
 * @retval Number of failed tests.
 */
int jat_run(const struct jat_test *tests, const char *name);

#endif /* _JAT_H_ */