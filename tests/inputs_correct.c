#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/token.h"
#include "../includes/header.h"
#include "../includes/parser.h"
#include <string.h>

/*
**	Ce fichier contient l'ensemble des commandes bash fonctionnelles
**	Il est amené à être amélioré avec le projet
**
*/

/* QUOTES TESTS */

typedef struct	s_input_test {
	char input[30];
	char result[30];
	int	flag;
}				t_tok_input_test;


ParameterizedTestParameters(quoting_suite, quotes_removal_test)
{
	static t_tok_input_test tests[] = {

		{ .input = "bonjour'bonjour", .result = "bonjour'bonjour", .flag = 0 | 1 << _NO_QUOTES },
		{ .input = "bonjour\"bonjour", .result = "bonjour\"bonjour", .flag = 0 | 1 << _NO_QUOTES },
		{ .input = "bon'jour\"bonjour", .result = "bon'jour\"bonjour", .flag = 0 | 1 << _NO_QUOTES },
		{ .input = "bonjour\"bonj'our", .result = "bonjour\"bonj'our", .flag = 0 | 1 << _NO_QUOTES },

		{ .input = "bonjour'bonjour\"bonjour\"", .result = "bonjour'bonjourbonjour", .flag = 0 | 1 << _DOUBLE_QUOTES},
		{ .input = "bonjourbonjour\"bonjour\"", .result = "bonjourbonjourbonjour", .flag = 0 | 1 << _DOUBLE_QUOTES},
		{ .input = "\"bonjour\"", .result = "bonjour", .flag = 0 | 1 << _DOUBLE_QUOTES},

		{ .input = "bonjour'bonjour'", .result = "bonjourbonjour", .flag = 0 | 1 << _SINGLE_QUOTES },
		{ .input = "'bonjour'bonjour", .result = "bonjourbonjour", .flag = 0 | 1 << _SINGLE_QUOTES},
		{ .input = "bonjour'bon\"jour'\"", .result = "bonjourbon\"jour\"", .flag = 0 | 1 << _SINGLE_QUOTES},

		{ .input = "'bonjour'\"bonjour\"", .result = "bonjourbonjour", .flag = 0 | 1 << _SINGLE_QUOTES | 1 << _DOUBLE_QUOTES},
/*
		{ .input = "", .result = ""},
		{ .input = "", .result = ""},
		{ .input = "", .result = ""},
*/
	};

	return (cr_make_param_array(t_tok_input_test, tests,
							   sizeof(tests)/sizeof(t_tok_input_test)));
}

ParameterizedTest(t_tok_input_test *params, quoting_suite, quotes_removal_test)
{
	char *str;
	t_token *token;
	str = params->input;
	token = get_next_token(&str);
	cr_assert_not_null(token, "for [%s]\ntoken should be allocated and this is not the case", params->input);
	word_flagger(token);
	cr_expect_eq(token->flag, params->flag, "for [%s]\ntoken flag should be [%x]\nInstead we got [%x]",
				 params->input, params->flag, token->flag);
	remove_quoting(token->cmd);
	cr_expect_str_eq(token->cmd, params->result);
	free_token(token);
}

/* REDIRECTIONS TESTS */

typedef struct	s_testing_cmd_parse{
	char		input[40];
	char		expected[40];
	t_tok_type		role;
}				t_testing_cmd_parse;

ParameterizedTestParameters(parser_suite, redirection_parse_test) {
	static t_testing_cmd_parse tests[] = {
	//Normal usage testing

		{ .expected = "<", .role = redirection, .input = "<file"},
		{ .expected = ">", .role = redirection, .input = ">file" },
		 { .expected = ">>", .role = redirection, .input = ">>file;" },
	//Testing with random spaces added

		{ .expected = "<", .role = redirection, .input = "< file"},
		{ .expected = ">", .role = redirection, .input = ">file" },
		 { .expected = ">>", .role = redirection, .input = "    >>file" },
	//Testing with double quotes added
		// { .expected = "\">>\"", .role = tok_command, .input = "\">>\"" },
	};

	return cr_make_param_array(t_testing_cmd_parse, tests, sizeof(tests) / sizeof(t_testing_cmd_parse));
}

ParameterizedTest(t_testing_cmd_parse *tests, parser_suite, redirection_parse_test)
{
	char *line = tests->input;
	t_block raw_result;
	int fct_ret = parse_simple_command(&raw_result, &line);

	t_simple_command	*testerino = raw_result.kind.cmd;
	t_redirection *redir =  testerino->redirections->content;
	t_token *token = redir->operator;

	cr_assert_eq(fct_ret, 0);
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
		 .expected_type[0] = word, .expected_type[1] = word,
		 .expected[20] = ""},

		{.input = "       echo   		           bonjour;",
		 .expected[0] = "echo", .expected[1] = "bonjour;",
		 .expected_type[0] = word, .expected_type[1] = word,
		 .expected[20] = ""},

		{.input = "echo   		           bonjour		; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";", .expected[3] = "ls",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = word, .expected_type[3] = word,
		 .expected[20] = ""},

		{.input = "echo   		           bonjour	>>file	; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";", .expected[3] = "ls",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = word, .expected_type[3] = word,
		 .expected[20] = ">>", .expected[21] = "file",
		 .expected_type[20] = redirection, .expected_type[21] = word },

		{.input = "	>>file echo   		           bonjour	; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";", .expected[3] = "ls",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = word, .expected_type[3] = word,
		 .expected[20] = ">>", .expected[21] = "file",
		 .expected_type[20] = redirection, .expected_type[21] = word },
		
		{.input = "	>>file > file echo   		           bonjour	; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";", .expected[3] = "ls",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = word, .expected_type[3] = word,
		 .expected[20] = ">>", .expected[21] = "file", .expected[22] = ">", .expected[23] = "file",
		 .expected_type[20] = redirection, .expected_type[21] = word, .expected_type[22] = redirection, .expected_type[23] = word },

		 {.input = "	>>file  echo   		> file           bonjour	; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";", .expected[3] = "ls",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = word, .expected_type[3] = word,
		 .expected[20] = ">>", .expected[21] = "file", .expected[22] = ">", .expected[23] = "file",
		 .expected_type[20] = redirection, .expected_type[21] = word, .expected_type[22] = redirection, .expected_type[23] = word },

		  {.input = "	>>file  echo   		> file           bonjour < file	; ls",
		 .expected[0] = "echo", .expected[1] = "bonjour", .expected[2] = ";", .expected[3] = "ls",
		 .expected_type[0] = word, .expected_type[1] = word, .expected_type[2] = word, .expected_type[3] = word,
		 .expected[20] = ">>", .expected[21] = "file", .expected[22] = ">", .expected[23] = "file", .expected[24] = "<", .expected[25] = "file",
		 .expected_type[20] = redirection, .expected_type[21] = word, .expected_type[22] = redirection, .expected_type[23] = word, .expected_type[24] = redirection, .expected_type[25] = word },

		{.input = "	>>file > file < file",
		 .expected[0] = "",
		 .expected[20] = ">>", .expected[21] = "file", .expected[22] = ">", .expected[23] = "file", .expected[24] = "<", .expected[25] = "file",
		 .expected_type[20] = redirection, .expected_type[21] = word, .expected_type[22] = redirection, .expected_type[23] = word, .expected_type[24] = redirection, .expected_type[25] = word },

	};

	return cr_make_param_array(scmd_test, tests, sizeof(tests) / sizeof(scmd_test));
}

ParameterizedTest(scmd_test *tests, parser_suite, simple_command_parse_test)
{

	char *line = tests->input;
	t_block llist;
	int fct_ret = parse_simple_command(&llist, &line);

	cr_assert_eq(fct_ret, 0);
	t_list *tmp;
	t_token	*token;
	int i;

	tmp = llist.kind.cmd->words;
	i = 0;
	if (tests->expected[0][0])
	{
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
	}

if (tests->expected[20][0])
	{
		t_list *tmp;
		t_token	*token;
		int word_index;
		int	redir_index;
		tmp = llist.kind.cmd->redirections;
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

Test(parsing_suite, simple_pipe_input_test)
{
	char *str = "ls | ls";
	char tab[5][10] = {"ls", "|", "ls", ""};

	// get first list of commands and pipelines
	t_list	*result = parser_loop(str);
	t_block	*internal_check = result->content;
	// isolate first lvl of abstraction (first node content)
	cr_assert_eq(internal_check->id, pipeline);
	int i = 0;

	t_pipeline *internal_pipe = internal_check->kind.pipe;
	t_list	*tmp = internal_pipe->commands;

	t_token	*token = tmp->content;

	cr_expect_eq(internal_pipe->pipe_count, 2);
	// isolate second lvl of abstraction (first command of first pipeline)
	t_simple_command *command = tmp->content;
	t_list	*tmp2 = command->words;
	
	
	while (tmp2)
	{
		//at the third lvl of abstraction (iterating on the nodes of the first command)
		token = tmp2->content;
		cr_assert_str_eq(token->cmd, tab[i]);
		i++;
		tmp2 = tmp2->next;
	}
}
