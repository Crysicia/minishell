#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include <fcntl.h>

// typedef struct	s_are_quotes_valid_params {
// 	bool ret;
// 	char *argument;
// }				t_are_quotes_valid_params;

// ParameterizedTestParameters(scanner_quotes_suite, are_quotes_valid_test) {
// 	static t_are_quotes_valid_params are_quotes_valid_params[] = {
// 		{ .ret = false, .argument = NULL },
// 		{ .ret = false, .argument = "'bonjour'\"" },
// 		{ .ret = false, .argument = "'bonjour''" },
// 		{ .ret = true, .argument = "'bonj\"our'" },
// 		{ .ret = true, .argument = "\" Bon ' jour\" ''" },
// 		{ .ret = true, .argument = "'bonjour\" tout le monde\"'" },
// 		{ .ret = true, .argument = "echo bonjour\" tout le monde\"" },
// 		{ .ret = true, .argument = "echo bonjour '|' cat -e" },
// 	};

// 	return cr_make_param_array(t_are_quotes_valid_params, are_quotes_valid_params, sizeof(are_quotes_valid_params) / sizeof(t_are_quotes_valid_params));
// }

// ParameterizedTest(t_are_quotes_valid_params *are_quotes_valid_params, scanner_quotes_suite, are_quotes_valid_test) {
// 	bool ret = are_quotes_valid(are_quotes_valid_params->argument);
// 	cr_expect(ret == are_quotes_valid_params->ret, "Expected are_quotes_valid to return [%d], instead got [%d]", are_quotes_valid_params->ret, ret);
// }

Test(scanner_quotes_suite, are_quotes_valid_test)
{
	cr_expect(are_quotes_valid(NULL) == false, "Expected are_quotes_valid to return false");
	cr_expect(are_quotes_valid("'bonjour'\"") == false, "Expected are_quotes_valid to return false");
	cr_expect(are_quotes_valid("'bonjour''") == false, "Expected are_quotes_valid to return false");
	cr_expect(are_quotes_valid("'bonj\"our'") == true, "Expected are_quotes_valid to return true");
	cr_expect(are_quotes_valid("\" Bon ' jour\" ''") == true, "Expected are_quotes_valid to return true");
	cr_expect(are_quotes_valid("'bonjour\" tout le monde\"'") == true, "Expected are_quotes_valid to return true");
	cr_expect(are_quotes_valid("echo bonjour\" tout le monde\"") == true, "Expected are_quotes_valid to return true");
	cr_expect(are_quotes_valid("echo bonjour '|' cat -e") == true, "Expected are_quotes_valid to return true");
}
