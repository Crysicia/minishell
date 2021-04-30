#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/token.h"

/*
**	All the tests done here ASSUMES that invalid quote input has been removed.
**	It does not check if quotes comes by pair.
**  We are also testing \
*/
typedef struct quotes_tests
{
	char	input[50];
	char	expected[50];
}			unit;

typedef struct antislash_tests
{
	char	input[50];
	char	expected[50];
}			antislash_unit_test;

ParameterizedTestParameters(quotes_removal_suite, testing_valid_input)
{
	static unit test[] = {
		{ .input = "''echo" , .expected = "echo"},
		{ .input = "'ech''o'" , .expected = "echo"},
		{ .input = "'ech''o'bonjour" , .expected = "echobonjour"},
		{ .input = "'ech'o'bonjour" , .expected = "echobonjour"},
	};
	return(cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *params, quotes_removal_suite, testing_valid_input)
{
	char buffer[4096];

	ft_bzero(buffer, 4096);
	remove_backslash(buffer, params->input);
	cr_expect_str_eq(buffer, params->expected);
}

ParameterizedTestParameters(antislash_removal_suite, testing_valid_input)
{
	static unit test[] = {
		{ .input = "\a\b\\c\\d\e" , .expected = "echo"},
		{ .input = "'ech''o'" , .expected = "echo"},
		{ .input = "'ech''o'bonjour" , .expected = "echobonjour"},
		{ .input = "'ech'o'bonjour" , .expected = "echobonjour"},
	};
	return(cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *params, antislash_removal_suite, testing_valid_input)
{
	char buffer[4096];

	ft_bzero(buffer, 4096);
	remove_simple_and_double_quotes(buffer, params->input);
	cr_expect_str_eq(buffer, params->expected);
}