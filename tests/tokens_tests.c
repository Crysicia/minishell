#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include "../includes/token.h"

void	init_empty_token(t_token *new)
{
	new->cmd = NULL;
	new->role = tok_end_of_cmd;
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
		{ .input = "echo bonjour", .expected = "echo", .result_tok = tok_word},
		{ .input = "echo", .expected = "echo", .result_tok = tok_word },
		{ .input = "echo       ", .expected = "echo", .result_tok = tok_word },
		{ .input = "echo;", .expected = "echo", .result_tok = tok_word },
		
		//testing ; isolation
		{ .input = ";", .expected = ";", .result_tok = tok_end_of_cmd },
		{ .input = ";    ", .expected = ";", .result_tok = tok_end_of_cmd },
		
		//testing > isolation
		{ .input = ">", .expected = ">", .result_tok = tok_redir_r},
		{ .input = ">    ", .expected = ">", .result_tok = tok_redir_r},
		{ .input = ">file ", .expected = ">", .result_tok = tok_redir_r},

		//testing < isolation
		{ .input = "<", .expected = "<", .result_tok = tok_redir_l},
		{ .input = "<     ", .expected = "<", .result_tok = tok_redir_l},
		{ .input = "<file", .expected = "<", .result_tok = tok_redir_l},
		
				//testing | isolation
		{ .input = "|", .expected = "|", .result_tok = tok_pipe},
		{ .input = "|   ", .expected = "|", .result_tok = tok_pipe},

		//testing >> isolation
		{ .input = ">>", .expected = ">>", .result_tok = tok_append_r},
		{ .input = ">>     ", .expected = ">>", .result_tok = tok_append_r},
		{ .input = ">>file", .expected = ">>", .result_tok = tok_append_r},
	};
	return (cr_make_param_array(tokens, tests, sizeof(tests)/sizeof(tokens)));
}

ParameterizedTest(tokens *params, token_attribution_suite, token_attribution_test)
{
	t_token *minishell;

	minishell = get_next_token(params->input);
	cr_expect_str_eq(minishell->cmd, params->expected,
	"Test_get_next_token = \nFor input : [%s] expected [%s] instead function returned [%s] instead",
			  params->input, params->expected, minishell->cmd);
	//cr_assert_eq(minishell->role, params->answer.role);

}
/*
Test(token_cutting_suite, token_cutting_backslash_test)
{
	char *input[] = { "\\ ", "   \\   ", "\\   ", "   \\ "};
	for (int i = 0; ((input + i) && *(input + i)); i++)
		cr_expect(strcmp(cut_token_string(input[i]), " ") == 0,
			"Please work your code to fit this condition on backslash");
}
*/