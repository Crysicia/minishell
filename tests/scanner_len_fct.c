#include <criterion/criterion.h>
#include <criterion/theories.h>
#include <signal.h>
#include <stdlib.h>
#include "../includes/finite_state_machine.h"

/*

TheoryDataPoints(scanner_suite, command_len_test) = {
	DataPoints(char *, "", ";", "echo", "ls -la", "ls -l -a", "echo salut", "echo salut;pwd"),
	DataPoints(size_t, 0, 0, 4, 5, 8, 10, 10),
};

Theory((char *test, size_t result), scanner_suite, command_len_test)
{
	cr_expect(command_len(test) == result,
	"command_len : expected %zu for %s ; got %zu\n",
	result, test, command_len(test));
}

*/



Test(scanner_suite, command_len_test)
{
	/*
		Careful this function does not handle many option case
	*/
	char 	*test[] = { "", ";", "echo", "ls -la", "ls -l", "ls -l -a", "echo salut", "echo salut;pwd", "env --verbose", "mkdir --verbose test;"};
	size_t	result[] = {0, 0, 4, 6, 5, 8, 10, 10, 13, 20};

	for (int i = 0; ((test + i) && (test[i])); i++)
		cr_expect(command_len(test[i]) == result[i],
		"command_len : expected %zu for %s ; got %zu\n",
		result[i], test[i], command_len(test[i]));
}


Test(scanner_suite, keyword_len_test)
{
	size_t results_expected[] = { 0, 0, 2, 4, 4, 7};
	char *test_input[] = { ";", "|", "ls -l", "echo", "echo foo | cat -e .", "/bin/ls"};

	for (int i = 0; i < 5; i++)
		cr_expect(keyword_len(test_input[i]) == results_expected[i],
		 "keyword_len did not return the right value, expected %zu for %s, got %zu\n", 
		 results_expected[i], test_input[i], keyword_len(test_input[i]));
}

Test(scanner_suite, option_len_test)
{
	char	*input[] = { "bonjour", "?", "-*cho", "-la", "--verbose" , "--verbose bonjour"};
	size_t	result[] = {0, 0, 0, 3, 9, 9};

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

Test(scanner_suite, command_len_failure, .signal = SIGSEGV){  		command_len(NULL); }
Test(scanner_suite, keyword_len_failure, .signal = SIGSEGV){  		keyword_len(NULL); }
Test(scanner_suite, option_len_failure, .signal = SIGSEGV){ 		option_len(NULL); }
Test(scanner_suite, argument_len_failure, .signal = SIGSEGV){ 		argument_len(NULL); }