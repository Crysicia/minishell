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

ParameterizedTestParameters(parser_suite, redirection_parse_test) {
	static t_testing_cmd_parse tests[] = {
	//Normal usage testing

		{ .expected = "<", .role = operator, .input = "<file"},
		{ .expected = ">", .role = operator, .input = ">file" },
		 { .expected = ">>", .role = operator, .input = ">>file" },
	//Testing with random spaces added

		{ .expected = "<", .role = operator, .input = "< file"},
		{ .expected = ">", .role = operator, .input = ">file" },
		 { .expected = ">>", .role = operator, .input = "    >>file" },
	//Testing with double quotes added
		// { .expected = "\">>\"", .role = tok_command, .input = "\">>\"" },
	};

	return cr_make_param_array(t_testing_cmd_parse, tests, sizeof(tests) / sizeof(t_testing_cmd_parse));
}

ParameterizedTest(t_testing_cmd_parse *tests, parser_suite, redirection_parse_test)
{
	char *line = tests->input;
	t_simple_command *llist;
	llist = parse_simple_command(&line);
	t_redirection *redir = llist->redirections->content;
	t_token *token = redir->operator;
	cr_expect(strcmp(token->cmd, tests->expected) == 0,
			 "expected [%s] output for [%s] input, instead, fct returned [%s]",
			  tests->expected, tests->input, token->cmd);
	cr_expect(token->role == tests->role,
			 "expected [%d] and got [%d] instead, input: [%s]",
			  tests->role, token->role, tests->input);
}

// test echo bonjour, get two token echo and bonjour and on last eventual redir
// systematic role testing + command type testing
typedef struct simple_cmd_unit_test {
	char input[60];
	char expected[40][40];
	t_tok_type	expected_type[40];
}			scmd_test;

ParameterizedTestParameters(parser_suite, simple_command_parse_test) {
	static scmd_test tests[] = {
	
		{.input = "echo bonjour",
		 .expected[0] = "echo", .expected[1] = "bonjour",
		 .expected[20] = "",
		 .expected_type[0] = word, .expected_type[1] = word },

		{.input = "echo   		           bonjour",
		 .expected[0] = "echo", .expected[1] = "bonjour",
		 .expected[20] = "",
		 .expected_type[0] = word, .expected_type[1] = word},

		{.input = "       echo   		           bonjour;",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";",
		 .expected[20] = "",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = operator },

		{.input = "echo   		           bonjour		; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";",
		 .expected[20] = "",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = operator },

		{.input = "echo   		           bonjour	>>file	; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";",
		 .expected[20] = ">>", .expected[21] = "file",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = operator,
		 .expected_type[20] = operator, .expected_type[21] = word },
	//Normal usage testing


		// { .expected = ">>", .role = tok_append_r, .input = ">>file" },
	//Testing with random spaces added

		// { .expected = ">>", .role = tok_append_r, .input = "    >>file" },
	//Testing with double quotes added
		// { .expected = "\">>\"", .role = tok_command, .input = "\">>\"" },
	};

	return cr_make_param_array(scmd_test, tests, sizeof(tests) / sizeof(scmd_test));
}

ParameterizedTest(scmd_test *tests, parser_suite, simple_command_parse_test)
{
	char *line = tests->input;
	t_simple_command *llist;
	llist = parse_simple_command(&line);

	t_list *tmp;
	t_token	*token;
	int i;

	tmp = llist->words;
	i = 0;
	while (tmp)
	{
		token = tmp->content;
		cr_expect_str_eq(token->cmd, tests->expected[i],
		"expected [%s] output for [%s] input, instead, fct returned [%s]",
		tests->expected[i], tests->input, token->cmd);
		cr_assert_eq(token->role, tests->expected_type[i]);
		i++;
		tmp = tmp->next;
	}

if (tests->expected[20][0])
	{
		t_list *tmp;
		t_token	*token;
		int word_index;
		int	redir_index;
		tmp = llist->redirections;
		word_index = 0;
		redir_index = 20;
		t_redirection *redir;
		while (tmp)
		{
			redir = tmp->content;
			token = redir->operator;
			cr_expect_str_eq(token->cmd, tests->expected[redir_index],
			"expected [%s] output for [%s] input, instead, fct returned [%s]",
			tests->expected[redir_index], tests->input, token->cmd);

			cr_assert_eq(token->role, tests->expected_type[redir_index]);
			
			token = redir->file;

			word_index++;
			redir_index++;
			cr_expect_str_eq(token->cmd, tests->expected[redir_index],
			"expected [%s] output for [%s] input, instead, fct returned [%s]",
			tests->expected[redir_index], tests->input, token->cmd);
			cr_assert_eq(token->role, tests->expected_type[redir_index]);

			word_index++;
			redir_index++;

			tmp = tmp->next;
		}
	}
}

//		{ .expected = "echo", .role = word, .input = "echo bonjour;"},
/************************************************************************************/
/*
		{ .expected = ";", .role = operator, .input = ";ls" },
		{ .expected = "|", .role = operator, .input = "|pwd" },
				{ .expected = ";", .role = operator, .input = "; ls" },

typedef struct quotes_examples
{
	char	input[200];
	int		result;
}			unit;

ParameterizedTestParameters(validating_quotes_suite, valid_tests)
{
	static unit test[] = {
	{.input = "'bonjo\"ur'", .result = 1},
	{.input = "bonjour", .result = 0},
	{.input = "bon'jo'ur", .result = 1},
	{.input = "\"'salut'\"", .result = 1},
	{.input = "\"bon'jour\"", .result = 1},
	};
	return(cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *test, validating_quotes_suite, valid_tests)
{
	int res = is_quoted(test->input);
	cr_assert_eq(res, test->result);
}

*/