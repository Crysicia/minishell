#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/token.h"

typedef struct	s_input_test {
	char input[20];
	char result[20];
}				t_tok_input_test;

ParameterizedTestParameters(tokenizer_suite, token_test)
{
	static t_tok_input_test tests[] = {
		{ .input = "echo bonjour ;", .result = "echo"},
		{ .input = "\"echo\" bonjour", .result = "\"echo\""},
		/* Double quotes usage */
		{ .input = "\"ls test\"", .result = "\"ls test\"" },
		{ .input = "\'pwd\'", .result = "\'pwd\'"},
		/* Single quotes normal use */
		{ .input = "\'cat file1 file2\'", .result = "\'cat file1 file2\'" },
		{ .input = "| bonjour", .result = "|" },
//		{ .input = "\\ hello", .result = " hello" },
	};

	return (cr_make_param_array(t_tok_input_test, tests,
								sizeof(tests)/sizeof(t_tok_input_test)));
}

ParameterizedTest(t_tok_input_test *params, tokenizer_suite, token_test)
{
	char *fct_ret;
	
	fct_ret = cut_token_string(params->input);
	cr_expect_str_eq(fct_ret, params->result,
			  "Test cut_token_string =\nFor input : [%s] expected [%s], function returned [%s] instead",
			  params->input, params->result, fct_ret);
}