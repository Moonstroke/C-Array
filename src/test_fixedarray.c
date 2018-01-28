#include "fixedarray.h"
#include "fixedarray_funcs.h"

#include <assert.h>
#include <log.h> /* for info(), verbose() */
#include <stdlib.h> /* for NULL */



static FixedArray *farray;
static const unsigned int test_farray_size = 8;
static int values[] = {1, 42, 6, 3, 27, 9, 55, 700};
static const unsigned int unset_index = 3;
static int extra_value = 33;
static void inc(data *const v) {
	++*(int*)v;
}
static const int values_swap_inc[] = {2, 43, 7, 34, 28, 10, 56, 701};
static const char *const fa_printf_output = "[2, 43, 7, 34, 28, 10, 56, 701]";
static void print_as_int(const data *const v) {
	if(v)
		printf("%d", *(int*)v);
	else
		printf("(null)");
}


void test_fixedarray(void) {

	log_setfilter(LOG_VERBOSE);


	info("construct a FixedArray: fa_new(%u)", test_farray_size);
	farray = fa_new(test_farray_size);
	assert(farray != NULL);
	info("OK\n");

	{
		FixedArray *expected, *got;
		info("test fa_new(%u)", 0);
		expected = NULL;
		verbose("Expected: %p", expected);
		got = fa_new(0);
		verbose("Got     : %p", got);
		assert(fa_new(0) == NULL);
		info("OK\n");
	}

	{
		unsigned int expected, got;
		info("test fa_size()");
		expected = test_farray_size;
		verbose("Expected: %u", expected);
		got = fa_size(farray);
		verbose("Got     : %u", got);
		assert(got == expected);
		info("OK\n");
	}

	{
		info("tests fa_set");
		for(unsigned int i = 0; i < test_farray_size; ++i) {
			data *const val = &values[i];
			verbose("fa_set(%u, %p)", i, val);
			fa_set(farray, i, val);
		}
		info("OK\n");
	}

	{
		info("tests fa_get");
		for(unsigned int i = 0; i < test_farray_size; ++i) {
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

	{
		int expected, got;
		info("test fa_unset(%u)", unset_index);
		expected = values[unset_index];
		verbose("Expected: %d", expected);
		got = *(int*)fa_unset(farray, unset_index);
		verbose("Got     : %d", got);
		assert(got == expected);
		info("OK\n");
	}

	{
		unsigned int expected, got;
		info("test fa_count()");
		expected = test_farray_size - 1;
		verbose("Expected: %u", expected);
		got = fa_count(farray);
		verbose("Got     : %u", got);
		assert(got == expected);
		info("OK\n");
	}

	{
		unsigned int expected, got;
		info("test fa_put(%d)", extra_value);
		expected = unset_index;
		verbose("Expected: %u", expected);
		got = fa_put(farray, (data*)&extra_value);
		verbose("Got     : %u", got);
		assert(got == expected);
		info("OK\n");
	}

	{
		info("test fa_each()");
		fa_each(farray, inc);
		verbose("Checking array elements...");
		for(unsigned int i = 0; i < test_farray_size; ++i) {
			const int expected = values_swap_inc[i],
			          got = *(int*)fa_get(farray, i);
			assert(got == expected);
			verbose("OK for %u", i);
		}
		info("OK\n");
	}

	{
		info("test fa_printf()");
		verbose("Expected output is:\n%s", fa_printf_output);
		verbose("Output got is:");
		fa_printf(farray, print_as_int);
		info("Please check manually.\n");
	}

	info("fa_free");
	fa_free(farray);
	info("OK\n");
}
