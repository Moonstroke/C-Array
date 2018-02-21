#include "fixedarray.h"
#include "fixedarray_funcs.h"

#include <assert.h>
#include <errno.h> /* for errno, EINVAL, ERANGE */
#include <log.h> /* for info(), verbose(), log_setfilter() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for NULL */



extern int errno;



static FixedArray *farray;

static const unsigned int INT_FIXED_ARRAY_SIZE = 8;
static int VALUES[] = {1, 42, 6, 3, 27, 9, 55, 700};

/* This value must be declared at global level, because it is used
   in fa_unset AND fa_put */
static const unsigned int unset_index = 3;

/* used for fa_cond and fa_remove */
static bool equal_as_ints(const data *const i, const data *const j) {
	assert(i != NULL && j != NULL);
	return *(int*)i == *(int*)j;
}
static const char equal_as_ints_repr[] = "(int *i, int *j) -> *i == *j";


static void init(void) {
	info("farray = fa_new(%u)", INT_FIXED_ARRAY_SIZE);
	farray = fa_new(INT_FIXED_ARRAY_SIZE);
	assert(farray != NULL);
	info("OK\n");
}

static void cleanup(void) {
	fa_free(farray);
}


static void test_fa_new__0_null(void) {
	FixedArray *got;
	info("test fa_new -- size of 0 => NULL");
	info("test fa_new(0)");
	verbose("expected: (nil)");
	got = fa_new(0);
	verbose("got     : %p", got);
	assert(got == NULL);
	assert(errno == EINVAL);
	info("OK\n");
}

static void test_fa_size(void) {
	unsigned int got;
	info("test fa_size");
	info("fa_size(farray)");
	verbose("expected: %u", INT_FIXED_ARRAY_SIZE);
	got = fa_size(farray);
	verbose("got     : %u", got);
	assert(got == INT_FIXED_ARRAY_SIZE);
	info("OK\n");
}

static void test_fa_set(void) {
	data *param;
	info("test fa_set");
	for(unsigned int index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		param = VALUES + index;
		info("fa_set(farray, %u, %p)", index, param);
		fa_set(farray, index, param);
		assert(errno == 0);
	}
	info("OK\n");
}

static void test_fa_get(void) {
	data *expected, *got;
	info("test fa_get");
	for(unsigned int index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		info("fa_get(farray, %u)", index);
		expected = VALUES + index;
		verbose("expected: %p", expected);
		got = fa_get(farray, index);
		verbose("got     : %p", got);
		assert(got == expected);
		assert(errno == 0);
	}
	info("OK\n");
}

static void test_fa_unset(void) {
	data *expected, *got;
	info("test fa_unset");
	info("fa_unset(farray, %u)", unset_index);
	expected = VALUES + unset_index;
	verbose("expected: %p", expected);
	got = fa_unset(farray, unset_index);
	verbose("got     : %p", got);
	assert(got == expected);
	assert(errno == 0);
	info("OK\n");
}

static void test_fa_count(void) {
	unsigned int expected, got;
	info("test fa_count");
	info("fa_count(farray)");
	expected = INT_FIXED_ARRAY_SIZE - 1;
	verbose("expected: %u", expected);
	got = fa_count(farray);
	verbose("got     : %u", got);
	assert(got == expected);
	info("OK\n");
}

static void test_fa_put__valid(void) {
	static int extra = 33;
	data *const param = &extra;
	int expected, got;
	info("test fa_put(farray, %d)", param);
	expected = unset_index;
	verbose("expected: %d", expected);
	got = fa_put(farray, param);
	verbose("got     : %d", got);
	assert(got == expected);
	info("OK\n");
}

static void test_fa_put__invalid(void) {
	int extra = 7;
	data *const param = &extra;
	int got;
	info("test fa_put -- invalid (array is full)");
	info("fa_put(farray, %p)", param);
	verbose("expected: -1");
	got = fa_put(farray, param);
	verbose("got     : %d", got);
	assert(got == -1);
	info("OK\n");
}

static void test_fa_cond__valid(void) {
	static int test_val = 55;
	data *const param = &test_val;
	data *expected, *got;
	info("test fa_cond -- valid element value: %d", test_val);
	info("fa_cond(farray, %s, %p)", equal_as_ints_repr, param);
	expected = VALUES + 6;
	verbose("expected: %p", expected);
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	assert(got == expected);
	assert(errno == 0);
	info("OK\n");
}

static void test_fa_cond__null(void) {
	const unsigned int index = 5;
	data *const param = VALUES + index;
	data *expected, *got;
	info("test fa_cond -- NULL as function (compare addresses)");
	info("fa_cond(farray, (nil), %p)", param);
	expected = VALUES + index;
	verbose("expected: %p", expected);
	got = fa_cond(farray, NULL, param);
	verbose("got     :", got);
	assert(got == expected);
	assert(errno == 0);
	info("OK\n");
}

static void test_fa_cond__invalid(void) {
	static int test_val = 83;
	data *const param = &test_val;
	data *got;
	info("test fa_cond -- invalid value: %d", test_val);
	info("fa_cond(farray, %s, %p)", equal_as_ints_repr, param);
	verbose("expected: (nil)");
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	assert(got == NULL);
	assert(errno == EINVAL);
	info("OK\n");
}

static void test_fa_remove__valid(void) {
	static int test_val = 6;
	data *const param = &test_val;
	data *expected, *got;
	info("test fa_remove -- valid element value: %d", test_val);
	info("fa_remove(farray, %s, %p)", equal_as_ints_repr, param);
	expected = VALUES + 2;
	verbose("expected: %p", expected);
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	assert(got == expected);
	assert(errno == 0);
	info("OK\n");
}

static void test_fa_remove__null(void) {
	const unsigned int index = 5;
	data *const param = VALUES + index;
	data *expected, *got;
	info("test fa_remove -- NULL as function (compare addresses)");
	info("fa_remove(farray, (nil), %p)", param);
	expected = VALUES + index;
	verbose("expected: %p", expected);
	got = fa_cond(farray, NULL, param);
	verbose("got     :", got);
	assert(got == expected);
	assert(errno == 0);
	info("OK\n");
}

static void test_fa_remove__invalid(void) {
	static int test_val = 37;
	data *const param = &test_val;
	data *got;
	info("test fa_remove -- invalid element value: %d", test_val);
	info("fa_remove(farray, %s, %p)", equal_as_ints_repr, param);
	verbose("expected: (nil)");
	got = fa_cond(farray, equal_as_ints, param);
	verbose("got     : %p", got);
	assert(got == NULL);
	assert(errno == EINVAL);
	info("OK\n");
}

static void inc(data *const v) {
	++*(int*)v;
}
static const char inc_repr[] = "(int i) {++i;}";
static void test_fa_each(void) {
	const int values_after[] = {2, 43, 7, 34, 28, 10, 56, 701};
	info("test fa_each");
	info("fa_each(farray, %s)", inc_repr);
	fa_each(farray, inc);
	verbose("Checking array elements...");
	for(unsigned int i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		assert(*(int*)fa_get(farray, i) == values_after[i]);
		verbose("OK for %u", i);
	}
	info("OK\n");
}


static void print_as_int(const data *const e) {
	if(e)
		printf("%d", *(int*)e);
	else
		printf("(null)");
}
void test_fixedarray(void) {

	init();


	test_fa_new__0_null();

	test_fa_size();

	test_fa_set();
	fa_printf(farray, print_as_int);

	test_fa_get();


	test_fa_unset();
	fa_printf(farray, print_as_int);

	test_fa_count();

	test_fa_put__valid();
	fa_printf(farray, print_as_int);

	test_fa_put__invalid();

	test_fa_cond__valid();

	test_fa_cond__null();

	test_fa_cond__invalid();

	test_fa_remove__valid();

	test_fa_remove__null();

	test_fa_remove__invalid();

	test_fa_each();
	fa_printf(farray, print_as_int);

	cleanup();
}
