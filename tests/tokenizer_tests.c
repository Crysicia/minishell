#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include "../includes/token.h"

typedef struct	s_token_test {
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
		{ .input = "   | bonjour", .result = "|" },
		{ .input = "\\ hello", .result = " hello" },
	};

	return (cr_make_param_array(t_tok_input_test, tests,
								sizeof(tests)/sizeof(t_tok_input_test)));
}

ParameterizedTest(t_tok_input_test *params, tokenizer_suite, token_test)
{
	char *fct_ret = cut_token_string(params->input);
	cr_expect(strcmp(fct_ret, params->result) == 0,
			  "for input : [%s] expected [%s] instead function returned [%s] instead",
			  params->input, params->result, fct_ret);
}

Test(token_cutting_suite, token_cutting_echo_test)
{
	char *input[] = { "echo", "   echo  ", "echo  ", "   echo"};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), "echo") == 0),
			"Please work your code to fit this condition");
}

Test(token_cutting_suite, token_cutting_semi_colon_test)
{
	char *input[] = { ";", "   ;  ", ";  ", "   ;"};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), ";") == 0),
			"Please work your code to fit this condition");
}

Test(token_cutting_suite, token_cutting_pipe_test)
{
	char *input[] = { ">", "   >  ", ">  ", "   >"};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), ">") == 0),
			"Please work your code to fit this condition");
}

Test(token_cutting_suite, token_cutting_chevronD_test)
{
	char *input[] = { ">>", "   >>  ", ">>  ", "   >>" , " >>file"};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), ">>") == 0),
			"Please work your code to fit this condition");
}

Test(token_cutting_suite, token_cutting_chevronG_test)
{
	char *input[] = { "<", "   <  ", "<  ", "   <"};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), "<") == 0),
			"Please work your code to fit this condition");
}

Test(token_cutting_suite, token_cutting_chevronG_test)
{
	char *input[] = { "|", "   |  ", "|  ", "   |"};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), "|") == 0),
			"Please work your code to fit this condition");
}

Test(token_cutting_suite, token_cutting_backslash_test)
{
	char *input[] = { "\\ ", "   \\   ", "\\   ", "   \\ "};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), " ") == 0),
			"Please work your code to fit this condition");
}
