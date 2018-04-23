#include <clog.h>
#include <cute.h>
#include <stdlib.h> /* for EXIT_SUCCESS */



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

	const CUTE_RunResults ** results;

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
