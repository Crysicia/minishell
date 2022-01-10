#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "../includes/flag.h"
#include "helpers.h"
#include <fcntl.h>

typedef struct env_test
{
	char	word[50];
	int		flag;
	char	expected[50];
}				unit;

ParameterizedTestParameters(expansion_suite, dollar_expansion_test)
{
	static unit test[] = {
		{.word = "$USER", .flag = 0 | 1 << _EXPANSION, .expected = "lpassera"},
		{.word = "$USER $PATH", .flag = 0 | 1 << _EXPANSION, .expected = "lpassera /etc"},

		{.word = "'bonjour'", .flag = 0 | 1 << _SINGLE_QUOTES, .expected = "bonjour"},
		{.word = "'$USER'", .flag = 0 | 1 << _SINGLE_QUOTES, .expected = "$USER"},
	
		{.word = "bonjour", .flag = 0 | 1 << _DOUBLE_QUOTES, .expected = "bonjour"},
		{.word = "\"$USER\"", .flag = 0 | 1 << _DOUBLE_QUOTES | 1 << _EXPANSION, .expected = "lpassera"},
		{.word = "\"$USE\"", .flag = 0 | 1 << _DOUBLE_QUOTES | 1 << _EXPANSION, .expected = ""},
		{.word = "\"$USER $PATH\"", .flag = 0 | 1 << _DOUBLE_QUOTES | 1 << _EXPANSION, .expected = "lpassera /etc"},

	};
	return (cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *params, expansion_suite, dollar_expansion_test)
{
	char *envp[] = { "OLDPWD=/home/bonjour", "PATH=/etc", "PWD=/home", "USER=lpassera", "EMPTY=", NULL };
	init_globals(envp);

	char	*alloc_param = strdup(params->word);
	t_token *fake_token = new_token(alloc_param, word);
	fake_token->flag = params->flag;

	expand_token(fake_token);
	remove_quoting(fake_token->cmd);
	cr_expect_str_eq(fake_token->cmd, params->expected);
}
