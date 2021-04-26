#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/token.h"
#include <stdbool.h>
typedef struct token_examples
{
	char		input[40];
	t_tok_type 	type;
	bool		expected;
}				tokens;

ParameterizedTestParameters(token_evaluation_suite, syntax_testing)
{
	static tokens tests[] = {
		{.input = ";", .type = tok_end_of_cmd, .expected = true},
		{.input = "|", .type = tok_pipe, .expected = true},
		{.input = ">", .type = tok_redir_r, .expected = true},
		{.input = ">>", .type = tok_append_r, .expected = true},
		{.input = "<", .type = tok_redir_l, .expected = true},
		{.input = " ;", .type = tok_end_of_cmd, .expected = false},
		{.input = ";n", .type = tok_end_of_cmd, .expected = false},
		{.input = " ;  ", .type = tok_end_of_cmd, .expected = false},
		{.input = ";   ", .type = tok_end_of_cmd, .expected = false},
	};
	return (cr_make_param_array(tokens, tests, sizeof(tests)/sizeof(tokens)));
}

ParameterizedTest(tokens *params, token_evaluation_suite, syntax_testing)
{
	t_token *token;

	token = new_token(params->input, params->type);
	cr_assert_eq(params->expected, is_valid_token(*token));
}