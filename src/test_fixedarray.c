#include "fixedarray.h"
#include "fixedarray_funcs.h"

#include <assert.h>
#include <log.h> /* for info(), verbose(), log_setfilter() */
#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for NULL */



static FixedArray *farray;

static const unsigned int INT_FIXED_ARRAY_SIZE = 8;
static int values[] = {1, 42, 6, 3, 27, 9, 55, 700};

/* This value must be declared at global level, because it is used
   in fa_unset AND fa_put */
static const unsigned int unset_index = 3;


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
	FixedArray *expected, *got;
	info("test fa_new -- size of 0 => NULL");
	info("test fa_new(%u)", 0);
	expected = NULL;
	verbose("expected: %p", expected);
	got = fa_new(0);
	verbose("got     : %p", got);
	assert(got == expected);
	info("OK\n");
}

static void test_fa_size(void) {
	unsigned int expected, got;
	info("test fa_size");
	info("fa_size(farray)");
	expected = INT_FIXED_ARRAY_SIZE;
	verbose("expected: %u", expected);
	got = fa_size(farray);
	verbose("got     : %u", got);
	assert(got == expected);
	info("OK\n");
}

static void test_fa_set(void) {
	data *param;
	info("test fa_set");
	for(unsigned int index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		param = values + index;
		info("fa_set(farray, %u, %p)", index, param);
		fa_set(farray, index, param);
	}
	info("OK\n");
}

static void test_fa_get(void) {
	data *expected, *got;
	info("test fa_get");
	for(unsigned int index = 0; index < INT_FIXED_ARRAY_SIZE; ++index) {
		info("fa_get(farray, %u)", index);
		expected = values + index;
		verbose("expected: %p", expected);
		got = fa_get(farray, index);
		verbose("got     : %p", got);
		assert(got == expected);
	}
	info("OK\n");
}

static void test_fa_unset(void) {
	data *expected, *got;
	info("test fa_unset");
	info("fa_unset(farray, %u)", unset_index);
	expected = values + unset_index;
	verbose("expected: %p", expected);
	got = fa_unset(farray, unset_index);
	verbose("got     : %p", got);
	assert(got == expected);
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
	static int extra = 7;
	data *const param = &extra;
	int expected, got;
	info("test fa_put -- invalid (array is full)");
	info("fa_put(farray, %p)", param);
	expected = -1;
	verbose("expected: %d", expected);
	got = fa_put(farray, param);
	verbose("got     : %d", got);
	assert(got == expected);
	info("OK\n");
}

static void inc(data *const v) {
	++*(int*)v;
}
static const char inc_repr[] = "(int i) {i++;}";
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

	test_fa_each();
	fa_printf(farray, print_as_int);

	cleanup();
}
