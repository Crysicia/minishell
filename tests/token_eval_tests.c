#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/token.h"
#include <stdbool.h>
typedef struct token_examples
{
	char		input[40];
	t_tok_type 	type;
	int		expected;
}				tokens;

ParameterizedTestParameters(token_evaluation_suite, is_operator_test)
{
		static tokens tests[] = {
		{.input = ";", .type = word, .expected = 0},
		{.input = "|", .type = operator, .expected = 1},
		{.input = ">", .type = redirection, .expected = 1},
		{.input = ">>", .type = redirection, .expected = 1},
		{.input = "<", .type = redirection, .expected = 1},
		{.input = " ;", .type = word, .expected = 0},
		{.input = ";n", .type = word, .expected = 0},
		{.input = " ;  ", .type = word, .expected = 0},
		{.input = ";   ", .type = word, .expected = 0},
	};
	return (cr_make_param_array(tokens, tests, sizeof(tests)/sizeof(tokens)));
}

ParameterizedTest(tokens *params, token_evaluation_suite, is_operator_test)
{
	t_token *token;

	token = new_token(params->input, params->type);
	if (params->type == redirection)
		cr_assert_eq(params->expected, is_redirection(token->cmd));
	else
		cr_assert_eq(params->expected, is_operator(token->cmd));
}
