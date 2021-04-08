#include <criterion/criterion.h>
#include <string.h>
#include <signal.h>
#include "../includes/finite_state_machine.h"

Test(scanner_suite, FSM_test)
{
	char *test[] = {";;","","env","echo bonjour"};
	int	expected_result[] = {-1, 3, 3, 1};
	int i = 0;
	while ((test + i) && test[i])
	{
		cr_assert(scan_in_keyword_state(test[i]) == expected_result[i]);
		i++;
	}
}

Test(failure, fail_test, .signal = SIGSEGV)
{
	scan_in_keyword_state(NULL);
}