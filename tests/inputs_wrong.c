#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/token.h"

typedef struct quotes_examples
{
	char	input[200];
}			unit;

ParameterizedTestParameters(validating_quotes_suite, invalid_tests)
{
	static unit test[] = {
	{.input = "'bonjour"},
	{.input = "'bonjo\"ur"},
	{.input = "'bonjo\"u\"r"},
	{.input = "bonjo\"ur"},
	{.input = "zeiovez\"bonuou"jf},
	};
	return(cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *test, validating_quotes_suite, invalid_tests)
{
	int res = is_quoted(test->input);

	cr_assert_eq(res, -1);
}
