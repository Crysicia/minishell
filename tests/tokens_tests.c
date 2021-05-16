#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include "../includes/token.h"

void	init_empty_token(t_token *new)
{
	new->cmd = NULL;
	new->role = operator;
}

typedef struct token_examples
{
	char		input[40];
	char		expected[40];
	t_tok_type	result_tok;
}				tokens;

ParameterizedTestParameters(token_attribution_suite, token_attribution_test)
{
	static tokens tests[] =
	{
		{ .input = "echo bonjour", .expected = "echo", .result_tok = word},
		{ .input = "echo", .expected = "echo", .result_tok = word },
		{ .input = "echo       ", .expected = "echo", .result_tok = word },
		{ .input = "echo;", .expected = "echo", .result_tok = word },
		
		//testing ; isolation
		{ .input = ";", .expected = ";", .result_tok = operator },
		{ .input = ";    ", .expected = ";", .result_tok = operator },
		
		//testing > isolation
		{ .input = ">", .expected = ">", .result_tok = redirection},
		{ .input = ">    ", .expected = ">", .result_tok = redirection},
		{ .input = ">file ", .expected = ">", .result_tok = redirection},

		//testing < isolation
		{ .input = "<", .expected = "<", .result_tok = redirection},
		{ .input = "<     ", .expected = "<", .result_tok = redirection},
		{ .input = "<file", .expected = "<", .result_tok = redirection},
		
				//testing | isolation
		{ .input = "|", .expected = "|", .result_tok = operator},
		{ .input = "|   ", .expected = "|", .result_tok = operator},

		//testing >> isolation

		{ .input = ">>", .expected = ">>", .result_tok = redirection},
		{ .input = ">>     ", .expected = ">>", .result_tok = redirection},
		{ .input = ">>file", .expected = ">>", .result_tok = redirection},
	};
	return (cr_make_param_array(tokens, tests, sizeof(tests)/sizeof(tokens)));
}

ParameterizedTest(tokens *params, token_attribution_suite, token_attribution_test)
{
	t_token *minishell;
	char	*ptr;

	ptr = strdup(params->input);
	minishell = get_next_token(&ptr);
	cr_expect_str_eq(minishell->cmd, params->expected,
	"Test_get_next_token = \nFor input : [%s] expected [%s] instead function returned [%s] instead",
			  params->input, params->expected, minishell->cmd);
	cr_assert_eq(minishell->role, params->result_tok);

}
