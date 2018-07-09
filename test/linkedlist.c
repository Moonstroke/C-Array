#include "linkedlist.h"
#include "linkedlist_funcs.h"

#include <CUTE/cute.h>
#include <clog.h> /* for logging macros */
#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */
#include <unistd.h> /* for ssize_t */



/* The instance of test case */
CUTE_TestCase *case_linkedlist;



static LinkedList *llist;

static int VALUES[] = {42, 3, 7, 13, 6};
static const size_t INT_LINKED_LIST_SIZE = 5;


extern _Bool equal_as_ints(const data_t*, const data_t*);
extern const char equal_as_ints_repr[];

extern void print_as_int(const data_t*);


static void init(void) {
	verbose("llist = ll_new()");
	llist = ll_new();
	CUTE_assertNotEquals(llist, NULL);
	for(size_t i = 0; i < INT_LINKED_LIST_SIZE; ++i) {
		ll_add(llist, i, &VALUES[i]);
	}
}

static void cleanup(void) {
	verbose("ll_free(llist)");
	ll_free(llist);
}


static void test_ll_len__empty(void) {
	LinkedList *empty_llist;
	size_t got;
	notice("test ll_len -- empty list");
	info("empty_llist = ll_new()");
	empty_llist = ll_new();
	verbose("ll_len(empty_llist)");
	info("expected: 0");
	got = ll_len(empty_llist);
	info("got     : %zu", got);
	CUTE_assertEquals(got, 0);
	ll_free(empty_llist);
	verbose("OK");
}

static void test_ll_append(void) {
	LinkedList *empty_llist;
	int expected, got;
	data_t *param;
	notice("tests ll_append");
	verbose("empty_llist = ll_new()");
	empty_llist = ll_new();
	for(size_t n = 0; n < INT_LINKED_LIST_SIZE; ++n) {
		param = VALUES + n;
		verbose("ll_append(empty_llist, %p)", param);
		expected = n;
		info("expected: %d", expected);
		got = ll_append(empty_llist, param);
		info("got     : %d", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	ll_free(empty_llist);
	verbose("OK");
}

static void test_ll_len__full(void) {
	size_t got;
	notice("test ll_len -- list full");
	verbose("ll_len(llist)");
	info("expected: %zu", INT_LINKED_LIST_SIZE);
	got = ll_len(llist);
	info("got     : %zu", got);
	CUTE_assertEquals(got, INT_LINKED_LIST_SIZE);
	verbose("OK");
}

static void test_ll_get__valid(void) {
	data_t *expected, *got;
	notice("test ll_get -- valid indices");
	for(size_t index = 0; index < INT_LINKED_LIST_SIZE; ++index) {
		verbose("ll_get(llist, %zu)", index);
		expected = VALUES + index;
		info("expected: %p", expected);
		got = ll_get(llist, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	verbose("OK");
}

static void test_ll_get__invalid(void) {
	const size_t invalid_indices[3] = {
		ll_len(llist),
		ll_len(llist) + 1,
		42
	};
	data_t *got;
	size_t index;
	notice("test ll_get -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("ll_get(llist, %zu)", index);
		info("expected: (nil)");
		got = ll_get(llist, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_ll_set__valid(void) {
	static int extra = 64;
	data_t *const param = &extra;
	const size_t index = 4;
	notice("test ll_set -- valid index");
	verbose("ll_set(llist, %zu, %p)", index, param);
	info("expected errno: 0");
	ll_set(llist, index, param);
	info("actual errno  : %d", errno);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_ll_set__invalid(void) {
	static int extra = 23;
	data_t *const param = &extra;
	const size_t invalid_indices[3] = {
		ll_len(llist),
		ll_len(llist) + 1,
		73 /* big "arbitrary" value */
	};
	size_t index;
	notice("tests ll_set -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("ll_set(llist, %zu, %p)", index, param);
		info("expected errno: %d", ERANGE);
		ll_set(llist, index, param);
		info("actual errno  : %d", errno);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_ll_add__valid(void) {
	static int extra = 8;
	data_t *const param = &extra;
	ssize_t expected, got;
	const size_t index = 3;
	notice("test ll_add -- valid index");
	info("ll_add(llist, %zu, %p)", index, param);
	expected = (ssize_t)index;
	info("expected: %zd", expected);
	got = ll_add(llist, index, param);
	info("got     : %zd", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_ll_add__invalid(void) {
	int extra = 9;
	data_t *const param = &extra;
	const size_t invalid_indices[3] = {
		ll_len(llist) + 1,
		ll_len(llist) + 2,
		668
	};
	ssize_t got;
	size_t index;
	notice("test ll_add -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("ll_add(llist, %zu, %p)", index, param);
		info("expected: -1");
		got = ll_add(llist, index, param);
		info("got     : %zd", got);
		CUTE_assertEquals(got, -1);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_ll_drop__valid(void) {
	data_t *expected, *got;
	const size_t index = 0;
	notice("test ll_drop -- valid index");
	info("ll_drop(llist, %zu)", index);
	expected = VALUES + index;
	info("expected: %p", expected);
	got = ll_drop(llist, index);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_ll_drop__invalid(void) {
	const size_t invalid_indices[3] = {
		ll_len(llist),
		ll_len(llist) + 1,
		99
	};
	data_t *got;
	size_t index;
	notice("test ll_drop -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		info("ll_drop(llist, %zu)", index);
		info("expected: (nil)");
		got = ll_drop(llist, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_ll_swap__valid(void) {
	static int extra = -32;
	data_t *const param = &extra;
	const size_t index = 2;
	data_t *expected, *got;
	notice("test ll_swap -- valid index");
	verbose("ll_swap(llist, %zu, %p)", index, param);
	expected = VALUES + index;
	info("expected: %p = %d", expected, *(int*)expected);
	got = ll_swap(llist, index, param);
	info("got     : %p = %d", got, *(int*)got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_ll_swap__invalid(void) {
	int extra = 4;
	data_t *const param = &extra;
	const size_t invalid_indices[3] = {
		ll_len(llist),
		ll_len(llist) + 1,
		13
	};
	data_t *got;
	size_t index;
	notice("test ll_swap -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("ll_swap(llist, %zu, %p)", index, param);
		info("expected: (nil)");
		got = ll_swap(llist, index, param);
		info("got     : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_ll_cond__found(void) {
	const int value = VALUES[1];
	const data_t *const param = &value;
	data_t *expected, *got;
	notice("test ll_cond -- found");
	expected = VALUES + 1;
	verbose("ll_cond(array, *%d, %s)", *(int*)param, equal_as_ints_repr);
	info("expected: %p", expected);
	got = ll_cond(llist, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_ll_cond__not_found(void) {
	static int value = 1024;
	data_t *const param = &value;
	data_t *got;
	notice("test ll_cond -- not found");
	verbose("ll_cond(array, *%d, %s)", value, equal_as_ints_repr);
	info("expected: (nil)");
	got = ll_cond(llist, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	verbose("OK");
}

static void test_ll_remove__found(void) {
	const int value = 13;
	const data_t *const param = &value;
	data_t *expected, *got;
	notice("test ll_remove -- item found");
	verbose("ll_remove(llist, %p, %s)", param, equal_as_ints_repr);
	expected = VALUES + 3;
	info("expected: %p", expected);
	got = ll_remove(llist, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_ll_remove__not_found(void) {
	const int value = 4096;
	const data_t *const param = &value;
	data_t *got;
	notice("test ll_remove -- item not found");
	verbose("ll_remove(llist, %p, %s)", param, equal_as_ints_repr);
	info("expected: (nil)");
	got = ll_remove(llist, param, equal_as_ints);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}


void build_case_linkedlist(void) {
	case_linkedlist = CUTE_newTestCase("Tests for LinkedList", 17);
	CUTE_setCaseBefore(case_linkedlist, init);
	CUTE_setCaseAfter(case_linkedlist, cleanup);
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_len__empty));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_append));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_len__full));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_get__valid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_get__invalid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_set__valid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_set__invalid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_add__valid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_add__invalid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_drop__valid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_drop__invalid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_swap__valid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_swap__invalid));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_cond__found));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_cond__not_found));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_remove__found));
	CUTE_addCaseTest(case_linkedlist, CUTE_makeTest(test_ll_remove__not_found));
}
