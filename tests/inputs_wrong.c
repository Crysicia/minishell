#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/token.h"

typedef struct quotes_examples
{
	char	input[200];
	int		result;
}			unit;

ParameterizedTestParameters(validating_quotes_suite, invalid_tests)
{
	static unit test[] = {
	{.input = "'bonjour", result = -1},
	{.input = "'bonjo\"ur", result = -1},
	{.input = "'bonjo\"u\"r", result = -1},
	{.input = "bonjo\"ur", result = -1},
	};
	return(cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTestParameters(validating_quotes_suite, valid_tests)
{
	static unit test[] = {
	{.input = "'bonjo\"ur'", result = 1},
	{.input = "bonjour", result = 0},
	{.input = "bon'jo'ur", result = 1},
	{.input = "\"'salut'\"", result = 1},
	{.input = "\"bon'jour\"", result = 1},
	};
	return(cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *test, validating_quotes_suite, invalid_tests)
{
	int res = is_quoted(test->input);
	cr_assert_eq(res, test->result);
}

ParameterizedTest(unit *test, validating_quotes_suite, valid_tests)
{
	int res = is_quoted(test->input);
	cr_assert_eq(res, test->result);
}