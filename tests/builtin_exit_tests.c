#include <mimick.h>
#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_exit_params {
	int exit_code;
	char arguments[10][100];
}			t_exit_params;


void mock_exit(void)
{
	return ;
}

mmk_mock_define (exit_mock_supervisor, void, int);

ParameterizedTestParameters(builtin_exit_suite, exit_args_test) {
	static  t_exit_params exit_params[] = {
		{ .exit_code = 32, .arguments = { "exit", "bonjour" } },
		{ .exit_code = 0, .arguments = { "exit" } },
		{ .exit_code = 42, .arguments = { "exit", "42" } },
		{ .exit_code = 24, .arguments = { "exit", "-42" } },
	};

	return cr_make_param_array(t_exit_params, exit_params, sizeof(exit_params) / sizeof(t_exit_params));
}

#define exit(a) = 0;
ParameterizedTest(t_exit_params *exit_params, builtin_exit_suite, exit_args_test, .exit_code = 0) {
	t_command command;
	command.args = (char **)exit_params->arguments;
	(void)command;

	// mmk_mock("exit@self", exit_mock_supervisor);
	// mmk_when(exit(0), .then_call = &mock_exit);

	builtin_exit(&command);
	cr_log_warn("EXIT CODE [%d]", g_last_exit_code);
	cr_expect(g_last_exit_code == exit_params->exit_code, "Expected exit to set exit_code to [%d], instead got [%d]", exit_params->exit_code);
}
