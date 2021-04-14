#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_echo_params {
	int exit_code;
	char printed[420];
	char arguments[10][100];
}			t_echo_params;


ParameterizedTestParameters(builtin_echo_suite, echo_valid_args_test) {
	static  t_echo_params echo_params[] = {
		{ .exit_code = 0, .printed = "\n", .arguments = { "echo" } },
		{ .exit_code = 0, .printed = "bonjour\n", .arguments = { "echo", "bonjour" } },
		{ .exit_code = 0, .printed = "", .arguments = { "echo", "-n" } },
		{ .exit_code = 0, .printed = "bonjour", .arguments = { "echo", "-n", "bonjour" } },
		{ .exit_code = 0, .printed = "bonjour", .arguments = { "echo", "-nnnnnnn", "bonjour" } },
		{ .exit_code = 0, .printed = "-nnnnnnnm bonjour\n", .arguments = { "echo", "-nnnnnnnm", "bonjour" } },
		{ .exit_code = 0, .printed = "bonjour", .arguments = { "echo", "-n", "-n", "bonjour" } },
		{ .exit_code = 0, .printed = "-m -n bonjour\n", .arguments = { "echo", "-m", "-n", "bonjour" } },
		{ .exit_code = 0, .printed = "--n\n", .arguments = { "echo", "--n" } },
		{ .exit_code = 0, .printed = ";\n", .arguments = { "echo", "\\;" } },
		{ .exit_code = 0, .printed = "\\\n", .arguments = { "echo", "\\\\;" } },
	};

	return cr_make_param_array(t_echo_params, echo_params, sizeof(echo_params) / sizeof(t_echo_params));
}

ParameterizedTest(t_echo_params *echo_params, builtin_echo_suite, echo_valid_args_test) {
	char *line;
	size_t size = 0;
	t_command command;
	FILE *fp = freopen("echo.test", "w", stdout);

	command.args = (char **)echo_params->arguments;
	int return_value = builtin_echo(&command);

	cr_expect(return_value == echo_params->exit_code, "Expected echo to return [%d], instead got [%d]", echo_params->exit_code);

	fclose(fp);
	fp = fopen("echo.test", "r");
	getline(&line, &size, fp);
	fclose(fp);

	cr_expect(strcmp(line, echo_params->printed) == 0, "Expected echo to print [%s], instead got [%s]", echo_params->printed, line);

	cr_free(line);
}
