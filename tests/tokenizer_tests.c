#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/token.h"

typedef struct	s_input_test {
	char input[30];
	char result[30];
}				t_tok_input_test;

/*
	Testing all the nasty quotes case.
*/

ParameterizedTestParameters(tokenizer_suite, token_test)
{
	static t_tok_input_test tests[] = {
		/* Mixed tests */
		{ .input = "echo bonjour ;", .result = "echo"},
		{ .input = "\"echo\" bonjour", .result = "\"echo\""},
		{ .input = "'ec'ho bonjour ;", .result = "'ec'ho"},
		{ .input = "'ec'\"ho\" bonjour ;", .result = "'ec'\"ho\""},
		{ .input = "'ec'\"ho\"bonjour ;", .result = "'ec'\"ho\"bonjour"},
		{ .input = "'ec'\"ho\"b''onjour ;", .result = "'ec'\"ho\"b''onjour"},
		/* Double quotes usage */
		{ .input = "\"ls test\"", .result = "\"ls test\"" },
		{ .input = "\'pwd\'", .result = "\'pwd\'"},
		/* Single quotes normal use */
		{ .input = "\'cat file1 file2\'", .result = "\'cat file1 file2\'" },
		{ .input = "| bonjour", .result = "|" },
		/* Mixed quoting */
		{ .input = "'bonjour'\"toi\"", .result = "'bonjour'\"toi\""},
		{ .input = "'bonjour' \"toi\"", .result = "'bonjour'"},
		{ .input = "'bo\"njou\"r' \"toi\"", .result = "'bo\"njou\"r'"},
		/* Antislash use */
		{ .input = "\\$TEST", .result = "\\$TEST"},

		/* words followed by different cases of quoting */
		{ .input = "bonjour'toi", .result = "bonjour'toi"},
		{ .input = "bonjour'toi'", .result = "bonjour'toi'"},
		{ .input = "bonjour'toi pikachu", .result = "bonjour'toi"},
		{ .input = "bonjour'toi bellatre''", .result = "bonjour'toi bellatre''"},
		{ .input = "bonjour'toi''", .result = "bonjour'toi''"},
		{ .input = "bonjour\"toi", .result = "bonjour\"toi"},
		{ .input = "bonjour\"'$USER'\"", .result = "bonjour\"'$USER'\""},
		{ .input = "bonjour\"'$USER'", .result = "bonjour\"'$USER'"},
		{ .input = "bonjour\"'$USER' toi", .result = "bonjour\"'$USER'"},
		{ .input = "\"'\"' toi", .result = "\"'\"'"},
		
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
