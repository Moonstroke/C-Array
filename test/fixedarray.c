#include "fixedarray.h"
#include "fixedarray_funcs.h"

#include <CUTE/cute.h>
#include <clog.h> /* for logging macros */
#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */



/* The instance of test case */
CUTE_TestCase *case_fixedarray;



static FixedArray *farray;

static const size_t INT_FIXED_ARRAY_SIZE = 8;
static int VALUES[] = {1, 42, 6, 3, 27, 9, 55, 700};


extern _Bool equal_as_ints(const data_t*, const data_t*);
extern const char equal_as_ints_repr[];

extern void print_as_int(const data_t*);


static void init(void) {
	verbose("farray = fa_new(%zu)", INT_FIXED_ARRAY_SIZE);
	farray = fa_new(INT_FIXED_ARRAY_SIZE);
	CUTE_assertNotEquals(farray, NULL);
	for(size_t i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		fa_set(farray, i, &VALUES[i]);
	}
}

static void cleanup(void) {
	verbose("fa_free(farray)");
	fa_free(farray);
}


static void test_fa_new__0_null(void) {
	FixedArray *got;
	notice("test fa_new -- size of 0 => NULL");
	verbose("fa_new(0)");
	info("expected: (nil)");
	got = fa_new(0);
	info("got     : %p", (void*)got); /* necessary cast because of GCC warning */
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_fa_size(void) {
	size_t got;
	notice("test fa_size");
	verbose("fa_size(farray)");
	info("expected: %zu", INT_FIXED_ARRAY_SIZE);
	got = fa_size(farray);
	info("got     : %zu", got);
	CUTE_assertEquals(got, INT_FIXED_ARRAY_SIZE);
	verbose("OK");
}

static void test_fa_set__valid(void) {
	data_t *param;
	notice("test fa_set -- valid indices");
	for(size_t index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		param = VALUES + index;
		verbose("fa_set(farray, %zu, %p)", index, param);
		fa_set(farray, index, param);
		info("expected errno: 0");
		info("got errno     : %d", errno);
		CUTE_assertNoError();
	}
	verbose("OK");
}

static void test_fa_set__invalid(void) {
	static int extra_value = 7;
	data_t *const param = &extra_value;
	const size_t invalid_indices[3] = {
		INT_FIXED_ARRAY_SIZE,
		INT_FIXED_ARRAY_SIZE + 1,
		3 * INT_FIXED_ARRAY_SIZE
	};
	size_t index;
	notice("test fa_set -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("fa_set(farray, %zu, %p)", index, param);
		info("expected errno: %d", ERANGE);
		fa_set(farray, index, param);
		info("got      errno: %d", errno);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_fa_get__valid(void) {
	data_t *expected, *got;
	notice("test fa_get -- valid indices");
	for(size_t index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		verbose("fa_get(farray, %zu)", index);
		expected = VALUES + index;
		info("expected: %p", expected);
		got = fa_get(farray, index);
		info("got     : %p", got);
		CUTE_assertEquals(got, expected);
		CUTE_assertNoError();
	}
	verbose("OK");
}

static void test_fa_get__invalid(void) {
	const size_t invalid_indices[3] = {
		INT_FIXED_ARRAY_SIZE,
		INT_FIXED_ARRAY_SIZE + 1,
		100
	};
	data_t *got;
	size_t index;
	notice("test fa_get -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("fa_get(farray, %zu)", index);
		info("expected : (nil)");
		got = fa_get(farray, index);
		info("got      : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_fa_unset__valid(void) {
	const size_t index = 5;
	data_t *expected, *got;
	notice("test fa_unset -- valid index");
	verbose("fa_unset(farray, %zu)", index);
	expected = VALUES + index;
	info("expected: %p", expected);
	got = fa_unset(farray, index);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_fa_unset__invalid(void) {
	const size_t invalid_indices[3] = {
		INT_FIXED_ARRAY_SIZE,
		INT_FIXED_ARRAY_SIZE + 1,
		43
	};
	data_t *got;
	size_t index;
	notice("test fa_unset -- invalid indices");
	for(size_t i = 0; i < 3; ++i) {
		index = invalid_indices[i];
		verbose("fa_unset(farray, %zu)", index);
		info("expected : (nil)");
		got = fa_unset(farray, index);
		info("got      : %p", got);
		CUTE_assertEquals(got, NULL);
		CUTE_assertErrnoEquals(ERANGE);
	}
	verbose("OK");
}

static void test_fa_count(void) {
	const size_t index = 3;
	size_t expected, got;
	notice("test fa_count");
	verbose("fa_unset(farray, %zu)", index);
	fa_unset(farray, index);
	verbose("fa_count(farray)");
	expected = INT_FIXED_ARRAY_SIZE - 1;
	info("expected: %zu", expected);
	got = fa_count(farray);
	info("got     : %zu", got);
	CUTE_assertEquals(got, expected);
	verbose("OK");
}

static void test_fa_put__valid(void) {
	static int extra = 33;
	const size_t index = 4;
	data_t *const param = &extra;
	ssize_t expected, got;
	notice("test fa_put");
	fa_unset(farray, index);
	verbose("fa_put(farray, %p)", param);
	expected = index;
	info("expected: %zd", expected);
	got = fa_put(farray, param);
	info("got     : %zd", got);
	CUTE_assertEquals(got, expected);
	verbose("OK");
}

static void test_fa_put__invalid(void) {
	int extra = 7;
	data_t *const param = &extra;
	ssize_t got;
	notice("test fa_put -- invalid (array is full)");
	verbose("fa_put(farray, %p)", param);
	info("expected: -1");
	got = fa_put(farray, param);
	info("got     : %zd", got);
	CUTE_assertEquals(got, -1);
	verbose("OK");
}

static void test_fa_cond__valid(void) {
	static int test_val = 55;
	data_t *const param = &test_val;
	data_t *expected, *got;
	notice("test fa_cond -- valid element value: %d", test_val);
	verbose("fa_cond(farray, %s, %p)", equal_as_ints_repr, param);
	expected = VALUES + 6;
	info("expected: %p", expected);
	got = fa_cond(farray, equal_as_ints, param);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_fa_cond__null(void) {
	const size_t index = 5;
	data_t *const param = VALUES + index;
	data_t *expected, *got;
	notice("test fa_cond -- NULL as function (compare addresses)");
	verbose("fa_cond(farray, (nil), %p)", param);
	expected = VALUES + index;
	info("expected: %p", expected);
	got = fa_cond(farray, NULL, param);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_fa_cond__invalid(void) {
	static int test_val = 83;
	data_t *const param = &test_val;
	data_t *got;
	notice("test fa_cond -- invalid value: %d", test_val);
	verbose("fa_cond(farray, %s, %p)", equal_as_ints_repr, param);
	info("expected: (nil)");
	got = fa_cond(farray, equal_as_ints, param);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void test_fa_remove__valid(void) {
	static int test_val = 6;
	data_t *const param = &test_val;
	data_t *expected, *got;
	notice("test fa_remove -- valid element value: %d", test_val);
	verbose("fa_remove(farray, %s, %p)", equal_as_ints_repr, param);
	expected = VALUES + 2;
	info("expected: %p", expected);
	got = fa_cond(farray, equal_as_ints, param);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_fa_remove__null(void) {
	const size_t index = 5;
	data_t *const param = VALUES + index;
	data_t *expected, *got;
	notice("test fa_remove -- NULL as function (compare addresses)");
	verbose("fa_remove(farray, (nil), %p)", param);
	expected = VALUES + index;
	info("expected: %p", expected);
	got = fa_cond(farray, NULL, param);
	info("got     : %p", got);
	CUTE_assertEquals(got, expected);
	CUTE_assertNoError();
	verbose("OK");
}

static void test_fa_remove__invalid(void) {
	static int test_val = 37;
	data_t *const param = &test_val;
	data_t *got;
	notice("test fa_remove -- invalid element value: %d", test_val);
	verbose("fa_remove(farray, %s, %p)", equal_as_ints_repr, param);
	info("expected: (nil)");
	got = fa_cond(farray, equal_as_ints, param);
	info("got     : %p", got);
	CUTE_assertEquals(got, NULL);
	CUTE_assertErrnoEquals(EINVAL);
	verbose("OK");
}

static void inc(data_t *const v) {
	++*(int*)v;
}
static const char inc_repr[] = "(int i) {++i;}";
static void test_fa_each(void) {
	int expected, got;
	notice("test fa_each");
	verbose("fa_each(farray, %s)", inc_repr);
	fa_each(farray, inc);
	for(size_t i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		expected = VALUES[i];
		info("expected at %zu: %d", i, expected);
		got = *(int*)fa_get(farray, i);
		info("got at %zu     : %d", i, got);
		CUTE_assertEquals(got, expected);
		verbose("OK for %zu", i);
	}
	verbose("OK");
}


void build_case_fixedarray(void) {
	case_fixedarray = CUTE_newTestCase("Tests for FixedArray", 18);
	CUTE_setCaseBefore(case_fixedarray, init);
	CUTE_setCaseAfter(case_fixedarray, cleanup);
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_new__0_null));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_size));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_set__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_set__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_get__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_get__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_unset__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_unset__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_count));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_put__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_put__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_cond__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_cond__null));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_cond__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_remove__valid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_remove__null));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_remove__invalid));
	CUTE_addCaseTest(case_fixedarray, CUTE_makeTest(test_fa_each));
}
