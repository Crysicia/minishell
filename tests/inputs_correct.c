#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/token.h"
#include "../includes/header.h"
#include <string.h>


/*
**	Ce fichier contient l'ensemble des commandes bash fonctionnelles
**	Il est amené à être amélioré avec le projet
**
*/

typedef struct	s_testing_cmd_parse{
	char		input[40];
	char		expected[40];
	t_tok_type		role;
}				t_testing_cmd_parse;

ParameterizedTestParameters(parser_suite, command_parse_test) {
	static t_testing_cmd_parse tests[] = {
	//Normal usage testing
		{ .expected = "echo", .role = word, .input = "echo bonjour;"},
		{ .expected = ";", .role = operator, .input = ";ls" },
		{ .expected = "|", .role = operator, .input = "|pwd" },
		{ .expected = "<", .role = operator, .input = "<file"},
		{ .expected = ">", .role = operator, .input = ">file" },
		// { .expected = ">>", .role = tok_append_r, .input = ">>file" },
	//Testing with random spaces added
		{ .expected = ";", .role = operator, .input = "; ls" },
		{ .expected = "<", .role = operator, .input = "< file"},
		{ .expected = ">", .role = operator, .input = ">file" },
		// { .expected = ">>", .role = tok_append_r, .input = "    >>file" },
	//Testing with double quotes added
		// { .expected = "\">>\"", .role = tok_command, .input = "\">>\"" },
	};

	return cr_make_param_array(t_testing_cmd_parse, tests, sizeof(tests) / sizeof(t_testing_cmd_parse));
}

ParameterizedTest(t_testing_cmd_parse *tests, parser_suite, command_parse_test)
{
	t_list *result_list = parse_to_list(tests->input);
	t_token *result = result_list->content;
	cr_expect(strcmp(result->cmd, tests->expected) == 0,
			 "expected [%s] output for [%s] input, instead, fct returned [%s]",
			  tests->expected, tests->input, result->cmd);
	cr_expect(result->role == tests->role,
			 "expected [%d] and got [%d] instead, input: %s",
			  tests->role, result->role, tests->input);
}
