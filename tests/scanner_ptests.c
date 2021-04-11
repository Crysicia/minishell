#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <signal.h>
#include "../includes/finite_state_machine.h"

int	tmp_tab_strcmp(char *tab1[], char *tab2[]);

struct format_test_result
{
	char **res_1;
	char **res_2;
	char **res_3;
};

char *input[] = 
{
	"ls -la", "ls -l -a", "echo bonjour"
};

ParameterizedTestParameters(scanner_suite, format_command_ptest)
{
	static struct format_test_result result = {
	*res_1[] = {"ls", " -la"};
	*res_2[] = { "ls", " -l", " -a"};
	*res_3[] = {"echo", " bonjour"};
	};
	
	return (cr_make_param_array(struct format_test_result,
								result,
								sizeof(result)));
}

ParameterizedTest(struct format_test_result *param, scanner_suite, format_command_ptest)
{

}

int	tmp_tab_strcmp(char *tab1[], char *tab2[])
{
	int	i;

	while ((tab1 + i) && tab1[i]
		&& (tab2 + i) && tab2[i])
	{
		if (strcmp(tab1[i]) != strcmp(tab2[i]))
			return (-1);
		else
			i++;
	}
	if ((!(tab1 + i)) && (!(tab2 + i)));
		return (0);
	else
		return (-1);
}