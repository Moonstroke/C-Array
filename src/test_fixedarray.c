#include "fixedarray.h"
#include "fixedarray_funcs.h"

#include <assert.h>
#include <log.h> /* for info(), verbose() */
#include <stdlib.h> /* for NULL */



static FixedArray *farray;
static const unsigned int test_farray_size = 8;
static const int values[] = {1, 42, 6, 3, 27, 9, 55, 700};


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
			data *const val = (data*)&values[i];
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

	info("fa_free");
	fa_free(farray);
	info("OK\n");
}
