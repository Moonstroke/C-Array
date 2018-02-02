#include "fixedarray.h"
#include "fixedarray_funcs.h"

#include <assert.h>
#include <log.h> /* for info(), verbose() */
#include <stdlib.h> /* for NULL */



static FixedArray *farray;

static const unsigned int INT_FIXED_ARRAY_SIZE = 8;
static int values[] = {1, 42, 6, 3, 27, 9, 55, 700};

/* This value must be declared at global level, because it is used
   in fa_unset AND fa_put */
static const unsigned int unset_index = 3;


static void init(void) {
	info("construct a FixedArray: fa_new(%u)", INT_FIXED_ARRAY_SIZE);
	farray = fa_new(INT_FIXED_ARRAY_SIZE);
	assert(farray != NULL);
	info("OK\n");
}

static void cleanup(void) {
	fa_free(farray);
}


static void test_fa_new__0_null(void) {
	FixedArray *expected, *got;
	info("test fa_new(%u)", 0);
	expected = NULL;
	verbose("Expected: %p", expected);
	got = fa_new(0);
	verbose("Got     : %p", got);
	assert(fa_new(0) == NULL);
	info("OK\n");
}

static void test_fa_size(void) {
	unsigned int expected, got;
	info("test fa_size()");
	expected = INT_FIXED_ARRAY_SIZE;
	verbose("Expected: %u", expected);
	got = fa_size(farray);
	verbose("Got     : %u", got);
	assert(got == expected);
	info("OK\n");
}

static void test_fa_set(void) {
	info("tests fa_set");
	for(unsigned int i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		data *const val = &values[i];
		verbose("fa_set(%u, %p)", i, val);
		fa_set(farray, i, val);
	}
	info("OK\n");
}

static void test_fa_get(void) {
	info("tests fa_get");
	for(unsigned int i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		int expected, got;
		verbose("fa_get(%u)", i);
		expected = values[i];
		verbose("Expected: %d", expected);
		got = *(int*)fa_get(farray, i);
		verbose("Got     : %d", got);
		assert(got == expected);
	}
	info("OK\n");
}

static void test_fa_unset(void) {
	int expected, got;
	info("test fa_unset(%u)", unset_index);
	expected = values[unset_index];
	verbose("Expected: %d", expected);
	got = *(int*)fa_unset(farray, unset_index);
	verbose("Got     : %d", got);
	assert(got == expected);
	info("OK\n");
}

static void test_fa_count(void) {
	unsigned int expected, got;
	info("test fa_count()");
	expected = INT_FIXED_ARRAY_SIZE - 1;
	verbose("Expected: %u", expected);
	got = fa_count(farray);
	verbose("Got     : %u", got);
	assert(got == expected);
	info("OK\n");
}

static void test_fa_put(void) {
	static int extra_value = 33;
	unsigned int expected, got;
	info("test fa_put(%d)", extra_value);
	expected = unset_index;
	verbose("Expected: %u", expected);
	got = fa_put(farray, &extra_value);
	verbose("Got     : %u", got);
	assert(got == expected);
	info("OK\n");
}

static void inc(data *const v) {
	++*(int*)v;
}
static void test_fa_each(void) {
	const int values_after[] = {2, 43, 7, 34, 28, 10, 56, 701};
	info("test fa_each()");
	fa_each(farray, inc);
	verbose("Checking array elements...");
	for(unsigned int i = 0; i < INT_FIXED_ARRAY_SIZE; ++i) {
		const int expected = values_after[i],
		          got = *(int*)fa_get(farray, i);
		assert(got == expected);
		verbose("OK for %u", i);
	}
	info("OK\n");
}


static void print_as_int(const data *const v) {
	if(v)
		printf("%d", *(int*)v);
	else
		printf("(null)");
}
void test_fixedarray(void) {

	log_setfilter(LOG_VERBOSE);

	init();


	test_fa_new__0_null();

	test_fa_size();

	test_fa_set();
	fa_printf(farray, print_as_int);

	test_fa_get();


	test_fa_unset();
	fa_printf(farray, print_as_int);

	test_fa_count();

	test_fa_put();
	fa_printf(farray, print_as_int);

	test_fa_each();
	fa_printf(farray, print_as_int);

	cleanup();
}
