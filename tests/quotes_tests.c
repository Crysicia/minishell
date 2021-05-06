#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/header.h"
#include "../includes/flag.h"

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

	cr_expect_str_eq(buffer, params->expected, , "hello\n");
}

/* We will create a fake token to pass to word_flagger fct */
/* This function is expected to check quoting validity and update the flag var */

typedef struct flagger_tests
{
	char		input[50];
	t_tok_type	role;
	int			expected;
}				flag_unit_test;

ParameterizedTestParameters(quote_flagger_suite, flag_test)
{	
	static	flag_unit_test	test[] = {
	

		{.input = "'bonjour'", .role = word, .expected = SINGLE_QUOTES},
		{.input = "'bo\"njou\"r'", .role = word, .expected = SINGLE_QUOTES},
	
		{.input = "'bon'jo'\nur'", .role = word, .expected = MIXED_QUOTES},
		{.input = "'bon'jo'ur'", .role = word, .expected = MIXED_QUOTES},
		{.input = "'bon'jo\"ur'\"", .role = word, .expected = MIXED_QUOTES},
		{.input = "\"pont\"-'levis'", .role = word, .expected = MIXED_QUOTES},
	
		{.input = "'bonjour", .role = word, .expected = QUOTING_ERROR},
		{.input = "'b'onjo'ur", .role = word, .expected = QUOTING_ERROR},
		{.input = "\"bonjour", .role = word, .expected = QUOTING_ERROR},
		{.input = "'\"bon'jour $U'SER\"", .role = word, .expected = QUOTING_ERROR},
		{.input = ";", .role = operator, .expected = 0}
	};
	return (cr_make_param_array(flag_unit_test, test, sizeof(test)/sizeof(flag_unit_test)));
}

ParameterizedTest(flag_unit_test *params, quote_flagger_suite, flag_test)
{
	t_token *fake_token;

	fake_token = new_token(params->input, params->role);
	word_flagger(fake_token);
	cr_expect_eq(fake_token->flag, params->expected,
	"error on %s use case, expected %x got %x\n", params->input, params->expected, fake_token->flag);
}

ParameterizedTestParameters(quote_flagger_suite, flag_double_quotes)
{	
	static	flag_unit_test	test[] = {
		{.input = "\\'bonjour", .role = word, .expected = 0},
		{.input = "\"bonjo\"ur", .role = word, .expected = DOUBLE_QUOTES},
		{.input = "\"bonjo\"ur $USER", .role = word, .expected = DOUBLE_QUOTES},
		{.input = "\"bon'jour $USER\"", .role = word, .expected = DOUBLE_QUOTES},
		{.input = "\"bon'jour '$USER\"", .role = word, .expected = DOUBLE_QUOTES},
	};
	return (cr_make_param_array(flag_unit_test, test, sizeof(test)/sizeof(flag_unit_test)));
}

ParameterizedTest(flag_unit_test *params, quote_flagger_suite, flag_double_quotes)
{
	char buffer[100];
	int fd;
	
	bzero(buffer, 100);
	int len = strlen(params->input);
	
	system("touch tmp");
	fd = open("tmp", O_WRONLY|O_TRUNC);
	write(fd, params->input, len);
	close(fd);

	fd = open("tmp", O_RDONLY);
	read(fd, buffer, len);
	close(fd);

	char *tmp = strdup(buffer);
	t_token *fake = new_token(tmp, params->role);
	word_flagger(fake);
	cr_expect_eq(fake->flag, params->expected,
	"error on %s use case, expected %x got %x string is %s\n",
	params->input, params->expected, fake->flag, tmp);
	system("rm -f tmp");
}
/****************************************************************************/
/* Temporary Disabled */
/* Other work needs to be done before this */
/*

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
	remove_simple_and_double_quotes(buffer_0, params->input);
	remove_backslash(buffer_1, buffer_0);
	cr_expect_str_eq(buffer_1, params->expected);
}
*/
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