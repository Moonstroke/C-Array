#include "sortedarray.h"


#include <CUTE/cute.h>
#include <clog.h> /* for logging macros */
#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */



/* The instance of test case */
CUTE_TestCase *case_sortedarray;



static SortedArray *sortedarray;

extern int cmp_as_ints(const data_t*, const data_t*);
extern const char cmp_as_ints_repr[];

static const size_t INT_SORTED_ARRAY_SIZE = 10;
static int VALUES[] = {9 ,7, 1, 5, 40, 95, 65, 13, 27, 82};
static int VALUES_SORTED[] = {1, 5, 7, 9, 13, 27, 40, 65, 82, 95};


static void init(void) {
	verbose("sortedarray = sa_new(%zu, %s)", INT_SORTED_ARRAY_SIZE,
	        cmp_as_ints_repr);
	sortedarray = sa_new(INT_SORTED_ARRAY_SIZE, cmp_as_ints);
	CUTE_assertNotEquals(sortedarray, NULL);
	for(size_t i = 0; i < INT_SORTED_ARRAY_SIZE; ++i) {
		const ssize_t r = sa_add(sortedarray, &VALUES[i]);
		CUTE_runTimeAssert(r >= 0);
	}
}

static void cleanup(void) {
	verbose("sa_free(sortedarray)");
	sa_free(sortedarray);
}


static void test_sa_new__0_null(void) {
	SortedArray *got;
	notice("test sa_new -- size 0 => NULL sortedarray");
	verbose("sa_new(0, NULL)");
	info("expected: (nil)");
	got = sa_new(0, cmp_as_ints);
	info("got     : %p", (void*)got); /* necessary cast because of GCC warning */
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_sa_size__empty(void) {
	SortedArray *empty_sarray;
	size_t got;
	notice("test sa_size -- empty SortedArray == 0");
	info("empty_sarray = sa_new(%zu, %s)", INT_SORTED_ARRAY_SIZE,
	     cmp_as_ints_repr);
	empty_sarray = sa_new(INT_SORTED_ARRAY_SIZE, cmp_as_ints);
	verbose("sa_size(empty_sarray)");
	info("expected: 0");
	got = sa_size(empty_sarray);
	info("got     : %zu", got);
	CUTE_assertEquals(got, 0);
	verbose("OK");
}

static void test_sa_size(void) {
	size_t got;
	notice("test sa_size(sortedarray) == %zu", INT_SORTED_ARRAY_SIZE);
	verbose("sa_size(sortedarray)");
	info("expected: %zu", INT_SORTED_ARRAY_SIZE);
	got = sa_size(sortedarray);
	info("got     : %zu", got);
	CUTE_assertEquals(got, INT_SORTED_ARRAY_SIZE);
	verbose("OK");
}

static void test_is_sorted__sa_get(void) {
	const size_t s = sa_size(sortedarray);
	int *expected, *got;
	notice("test sortedarray is actually sorted");
	for(size_t i = 0; i < s; ++i) {
		verbose("sa_get(sortedarray, %zu)", i);
		expected = &VALUES_SORTED[i];
		info("expected: %d", *expected);
		got = sa_get(sortedarray, i);
		info("got     : %d", *got);
		CUTE_assertEqualsUsing(got, expected, cmp_as_ints, 0);
	}
	verbose("OK");
}

static void test_sa_indexof(void) {
	size_t expected, got;
	notice("test sa_indexof");
	for(size_t i = 0; i < INT_SORTED_ARRAY_SIZE; ++i) {
		verbose("sa_indexof(sortedarray, %zu)", i);
		expected = i;
		info("expected: %zu", expected);
		got = sa_indexof(sortedarray, &VALUES_SORTED[i]);
		info("got     : %zu", got);
		CUTE_assertEquals(got, expected);
	}
	verbose("OK");
}

static void test_sa_add__last(void) {
	static int extra = 1024;
	data_t *const param = &extra;
	ssize_t expected, got;
	notice("test sa_add() -- add item last in array");
	verbose("sa_add(sortedarray, %p)", param);
	expected = INT_SORTED_ARRAY_SIZE;
	info("expected: %zu", expected);
	got = sa_add(sortedarray, param);
	info("got     : %zu", got);
	CUTE_assertEquals(got, expected);
	verbose("OK");
	// a-posteriori check of the value actually set
	info("A posteriori validity check: sa_get(sortedarray, %zu) == %p",
	     INT_SORTED_ARRAY_SIZE, param);
	CUTE_assertEquals(sa_get(sortedarray, INT_SORTED_ARRAY_SIZE), param);
}

void build_case_sortedarray(void) {
	case_sortedarray = CUTE_newTestCase("Tests for SortedArray", 6);
	CUTE_setCaseBefore(case_sortedarray, init);
	CUTE_setCaseAfter(case_sortedarray, cleanup);
	CUTE_addCaseTest(case_sortedarray, CUTE_makeTest(test_sa_new__0_null));
	CUTE_addCaseTest(case_sortedarray, CUTE_makeTest(test_sa_size__empty));
	CUTE_addCaseTest(case_sortedarray, CUTE_makeTest(test_sa_size));
	CUTE_addCaseTest(case_sortedarray, CUTE_makeTest(test_is_sorted__sa_get));
	CUTE_addCaseTest(case_sortedarray, CUTE_makeTest(test_sa_indexof));
	CUTE_addCaseTest(case_sortedarray, CUTE_makeTest(test_sa_add__last));
}
