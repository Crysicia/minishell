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
		{.word = "'bonjour'", .flag = SINGLE_QUOTES, .expected = "'bonjour'"},
		{.word = "bonjour", .flag = DOUBLE_QUOTES, .expected = "bonjour"},
		{.word = "$USER", .flag = 0, .expected = "lpassera"},
		{.word = "\"$USER\"", .flag = DOUBLE_QUOTES, .expected = "\"lpassera\""},
		{.word = "\"$USE\"", .flag = DOUBLE_QUOTES, .expected = "\"\""}
	};
	return (cr_make_param_array(unit, test, sizeof(test)/sizeof(unit)));
}

ParameterizedTest(unit *params, expansion_suite, dollar_expansion_test)
{
	char *envp[] = { "OLDPWD=/home/bonjour", "PATH=/etc", "PWD=/home", "USER=lpassera", "EMPTY=", NULL };
	init_globals(envp);

	t_token *fake_token = new_token(params->word, word);
	fake_token->flag = params->flag;

	dollar_expansion(fake_token);
	cr_expect_str_eq(fake_token->cmd, params->expected);
}
