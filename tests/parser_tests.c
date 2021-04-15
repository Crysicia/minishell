#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/token.h"
#include "../includes/header.h"
#include <string.h>

t_token *parse_command(char *str)
{
	(void)str;
	t_token *new = malloc(sizeof(t_token));
	new->cmd = strdup("echo bonjour");
	new->role = tok_command;
	return (new);
}

typedef struct	s_testing_cmd_parse{
	char		input[40];
	char		expected[40];
	t_tok_type		role;
}				t_testing_cmd_parse;

ParameterizedTestParameters(parser_suite, command_parse_test) {
	static t_testing_cmd_parse tests[] = {
	//Normal usage testing
		{ .expected = "echo bonjour", .role = tok_command, .input = "echo bonjour;"},
		{ .expected = ";", .role = tok_end_of_cmd, .input = ";ls" },
		{ .expected = "|", .role = tok_pipe, .input = "|pwd" },
		{ .expected = "<", .role = tok_redir_l, .input = "<file"},
		{ .expected = ">", .role = tok_redir_r, .input = ">file" },
		{ .expected = ">>", .role = tok_append_r, .input = ">>file" },
	//Testing with random spaces added
		{ .expected = ";", .role = tok_end_of_cmd, .input = "; ls" },
		{ .expected = "<", .role = tok_redir_l, .input = "< file"},
		{ .expected = ">", .role = tok_redir_r, .input = ">file" },
		{ .expected = ">>", .role = tok_append_r, .input = "    >>file" },
	//Testing with double quotes added
		{ .expected = "\">>\"", .role = tok_command, .input = "\">>\"" },
	};

	return cr_make_param_array(t_testing_cmd_parse, tests, sizeof(tests) / sizeof(t_testing_cmd_parse));
}

ParameterizedTest(t_testing_cmd_parse *tests, parser_suite, command_parse_test)
{
	t_token *result = parse_command(tests->input);
	cr_expect(strcmp(result->cmd, tests->expected) == 0,
			 "expected [%s] output for [%s] input, instead, fct returned [%s]",
			  tests->expected, tests->input, result->cmd);
	cr_expect(result->role == tests->role,
			 "expected [%d] and got [%d] instead",
			  tests->role, result->role);
}