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

void	remove_backslash(char *buffer, char *to_trim)
{
	buffer = NULL;
	to_trim = buffer;
	(void)to_trim;
}

typedef struct quotes_tests
{
	char	input[50];
	char	expected[50];
}			unit;

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
	remove_simple_and_double_quotes(buffer, params->input);

	cr_log_warn("hello, %s\n", buffer);
	cr_expect_str_eq(buffer, params->expected, , "hello\n");
}

/****************************************************************************/
typedef struct antislash_tests
{
	char	input[50];
	char	expected[50];
}			antislash_unit_test;

ParameterizedTestParameters(antislash_removal_suite, testing_valid_input)
{
	static unit test[] = {
	//	{ .input = "\a\b\\c\\d\e" , .expected = "echo"},
		{ .input = "'ech''o'" , .expected = "echo"},
		{ .input = "'ech\'\'o\'bonjour" , .expected = "ech''o'bonjour"},
		{ .input = "'ech'o\'bonjour" , .expected = "echobonjour"},
	};
	return(cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *params, antislash_removal_suite, testing_valid_input)
{
	char buffer_0[4096];
	char buffer_1[4096];

	ft_bzero(buffer_0, 4096);
	ft_bzero(buffer_1, 4096);
	remove_simple_and_double_quotes(buffer, params->input);
	remove_backslash(buffer, params->input);
	cr_expect_str_eq(buffer, params->expected);
}
/*

 echo 'bonjou\''
> -bash: unexpected EOF while looking for matching `''
-bash: syntax error: unexpected end of file
. echo 'bonjou\'
bonjou\
. echo 'bonjou\'eif'
> -bash: unexpected EOF while looking for matching `''
-bash: syntax error: unexpected end of file
. echo 'bonjou\'eif
bonjou\eif
. echo 'bo'njou\'eif
bonjou'eif
. echo 'bo'nj'ou\'eif
bonjou\eif
. echo 'bo'nj'ou\'ei'f
> ^C
. echo 'bo'njou\'ei'f
> ^C
. echo 'bo'njou\'eif
bonjou'eif
. echo 'bonjou\'eif
bonjou\eif

echo "bonjo\ur"
> bonjo\ur

echo "bon\'\"jo\ur" 
> bon\'"jo\ur

*/