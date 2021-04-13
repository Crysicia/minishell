#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#include "../includes/token.h"

typedef struct	s_token_test {
	enum e_token tok;
	char input[5];
}				t_token_test;

ParameterizedTestParameters(tokenizer_suite, token_test)
{
	static t_token_test tests[] = {
		{ .tok = end_of_cmd , .input = ";"},
		{ .tok = pipe, .input = "|" },
		{ .tok = redir_l, .input = "<" },
		{ .tok = redir_r, .input = ">" },
		{ .tok = append_r, .input = ">>"},
		{ .tok = command, .input = " echo bonjour "}
	};

}

ParameterizedTest(t_token_test *params, tokenizer_suite, token_test)
{

}
