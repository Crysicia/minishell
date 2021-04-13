#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/token.h"
#include "../includes/header.h"
#include <string.h>

t_tmp *parse_command(char *str)
{
	t_tmp *new = malloc(sizeof(t_tmp));
	new->cmd = strdup("hahah");
	new->role = pipe;
	return (new);
}

typedef struct	s_testing_cmd_parse{
	char		input[40];
	char		expected[40];
	enum e_role role;
}				t_testing_cmd_parse;

ParameterizedTestParameters(parser_suite, command_parse_test) {
	static t_testing_cmd_parse tests[] = {
	//Normal usage testing
		{ .expected = "echo bonjour", .role = command, .input = "echo bonjour;"},
		{ .expected = ";", .role = end_of_cmd, .input = ";ls" },
		{ .expected = "|", .role = pipe, .input = "|pwd" },
		{ .expected = "<", .role = redir_l, .input = "<file"},
		{ .expected = ">", .role = redir_r, .input = ">file" },
		{ .expected = ">>", .role = append_r, .input = ">>file" },
	//Testing with random spaces added
		{ .expected = ";", .role = end_of_cmd, .input = "; ls" },
		{ .expected = "<", .role = redir_l, .input = "< file"},
		{ .expected = ">", .role = redir_r, .input = ">file" },
		{ .expected = ">>", .role = append_r, .input = "    >>file" },
	//Testing with double quotes added
		{ .expected = "\">>\"", .role = command, .input = "\">>\"" },
	};

	return cr_make_param_array(t_testing_cmd_parse, tests, sizeof(tests) / sizeof(t_testing_cmd_parse));
}

ParameterizedTest(t_testing_cmd_parse *tests, parser_suite, command_parse_test)
{
	t_tmp *result = parse_command(tests->input);
	cr_expect(strcmp(result->test, tests->expected) == 0,
			 "expected [%s] output for [%s] input, instead, fct returned [%s]",
			  tests->expected, tests->input, result->cmd);
	cr_expect(result->role == tests->role,
			 "expected [%d] and got [%d] instead",
			  tests->role, result->role);
}
