#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <signal.h>
#include "../includes/finite_state_machine.h"

Test(scanner_suite, is_valid_command_test)
{
	int i;
	char *right_tests[] = { "pwd", "echo_bonjour" };
	for (i = 0; i < 2; i++)
		cr_assert(is_valid_command(right_tests[i]) == 1);

	char *wrong_tests[] = {	";;" };
	for (i = 0; i < 1; i++)
		cr_assert(is_valid_command(wrong_tests[i]) == 0);
}

Test(scanner_suite, evaluate_command_test)
{
	char *test_1_input = strdup("echo bonjour");
	char *test_1_result[] = {"echo", "bonjour"};
	char **fct_output = evaluate_command(test_1_input);

	cr_expect(strcmp(fct_output[0], test_1_result[0]) == 0, "first line for echo bonjour is not the same");
	cr_expect(strcmp(fct_output[1], test_1_result[1]) == 0, "second line for echo bonjour is not the same");

	cr_free(test_1_input);
	char **tmp = fct_output;
	while (tmp && *tmp)
		cr_free(*(tmp++));
	cr_free(fct_output);
}
/*
struct format_test_result = {
	*res_1[] = {"ls", "-la"};
	*res_2[] = { "ls", " -l", " -a"};

};

ParameterizedTestParameters(scanner_suite, format_command_ptest)
{
	static struct result = {};
}

*/
Test(scanner_suite, is_valid_command_failure, .signal = SIGSEGV){	is_valid_command(NULL); }
Test(scanner_suite, evaluate_command_failure, .signal = SIGSEGV){	evaluate_command(NULL); }
