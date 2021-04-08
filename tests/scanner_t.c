#include <criterion/criterion.h>
#include <string.h>
#include <signal.h>
//#include "../includes/grammar.h"
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

TheoryDataPoints(scanner_suite, command_len_test) = {
	DataPoints(char *, "", ";", "echo", "ls -la", "ls -l -a", "echo salut", "echo salut;pwd"),
	DataPoints(size_t, 0, 0, 4, 5, 8, 10, 10)
}

Theory((char *test, size_t result), scanner_suite, command_len_test) = {
	cr_expect(command_len(test) == result,
	"command_len : expected %zu for %s ; got %zu\n",
	result, test, command_len(test));
}

Test(scanner_suite, keyword_len_test)
{
	size_t results_expected[] = { 0, 0, 4, 4, 7};
	char *test_input[] = { ";", "|", "echo", "echo foo | cat -e .", "/bin/ls"};

	for (int i = 0; i < 5; i++)
		cr_expect(keyword_len(test_input[i]) == results_expected[i],
		 "keyword_len did not return the right value, expected %zu for %s, got %zu\n", 
		 results_expected[i], test_input[i], keyword_len(test_input[i]));
}

Test(scanner_suite, option_len_test)
{
	char	*input[] = { "bonjour", "?", "-*cho", "-la", "--verbose"};
	size_t	result[] = {0, 0, 0, 3, 9};

	for (int i = 0; i < 5; i++)
		cr_expect(option_len(input[i]) == result[i],
		"option_len did not return the right value, expected %zu for %s, got %zu\n", 
		 result[i], input[i], option_len(input[i])); 

}

Test(scanner_suite, argument_len_test)
{
	char	*input[] = { ";", "", "test; cat  -e .", "bonjour", "Salvador Dali"};
	size_t	result[] = { 0, 0, 4, 7, 13};

	for (int i = 0; i < 5; i++)
		cr_expect(argument_len(input[i]) == result[i],
		"argument_len did not return the right value, expected %zu for %s, got %zu\n", 
		 result[i], input[i], argument_len(input[i])); 

}

Test(scanner_suite, is_valid_command_failure, .signal = SIGSEGV){	is_valid_command(NULL); }
Test(scanner_suite, evaluate_command_failure, .signal = SIGSEGV){	evaluate_command(NULL); }
Test(scanner_suite, command_len_failure, .signal = SIGSEGV){  		command_len(NULL); }
Test(scanner_suite, keyword_len_failure, .signal = SIGSEGV){  		keyword_len(NULL); }
Test(scanner_suite, option_len_failure, .signal = SIGSEGV){ 		option_len(NULL); }
Test(scanner_suite, argument_len_failure, .signal = SIGSEGV){ 		argument_len(NULL); }