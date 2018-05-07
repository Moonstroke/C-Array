#include <clog.h> /* for clog_init */
#include <CUTE/cute.h>
#include <stdbool.h>
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for EXIT_SUCCESS */

#include "cods.h"



/* Helper functions */
bool equal_as_ints(const data *const e1, const data *const e2) {
	CUTE_runTimeAssert(e1 != NULL && e2 != NULL);
	return *(int*)e1 == *(int*)e2;
}
const char equal_as_ints_repr[] = "(int *i, int *j) -> *i == *j";

void print_as_int(const void *const e) {
	if(e)
		printf("%d", *(int*)e);
	else
		printf("(null)");
}


/* Declarations of the tests cases */
extern CUTE_TestCase *case_fixedarray;
extern void build_case_fixedarray(void);

extern CUTE_TestCase *case_array;
extern void build_case_array(void);

extern CUTE_TestCase *case_bitarray;
extern void build_case_bitarray(void);

extern CUTE_TestCase *case_linkedlist;
extern void build_case_linkedlist(void);


int main(void) {

	const CUTE_RunResults **results;

	clog_init(CLOG_FORMAT_TEXT, CLOG_ATTR_FUNC | CLOG_ATTR_COLORED);
	build_case_fixedarray();
	build_case_array();
	build_case_bitarray();
	build_case_linkedlist();

	CUTE_prepareTestSuite(4, case_fixedarray, case_array, case_bitarray,
	                      case_linkedlist);

	results = CUTE_runTestSuite();

	CUTE_printResults(4, results);


	return EXIT_SUCCESS;
}
