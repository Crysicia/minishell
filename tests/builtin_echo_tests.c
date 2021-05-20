#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include <sys/stat.h>
#include "helpers.h"

#include <stdio.h>
#include <fcntl.h>


typedef struct s_echo_params {
	char printed[420];
	char arguments[10][100];
}			t_echo_params;


ParameterizedTestParameters(builtin_echo_suite, echo_valid_args_test) {
	static  t_echo_params test[] = {
		{  .printed = "\n", .arguments[0] = "echo" },
		/*
		{  .printed = "bonjour\n", .arguments = { "echo", "bonjour", "" } },
		{  .printed = "", .arguments = { "echo", "-n", "" } },
		{  .printed = "bonjour", .arguments = { "echo", "-n", "bonjour", "" } },
		{  .printed = "bonjour", .arguments = { "echo", "-nnnnnnn", "bonjour", "" } },
		{  .printed = "-nnnnnnnm bonjour\n", .arguments = { "echo", "-nnnnnnnm", "bonjour", "" } },
		{  .printed = "bonjour", .arguments = { "echo", "-n", "-n", "bonjour", "" } },
		{  .printed = "-m -n bonjour\n", .arguments = { "echo", "-m", "-n", "bonjour", "" } },
		{  .printed = "--n\n", .arguments = { "echo", "--n", "" } },
		{  .printed = ";\n", .arguments = { "echo", "\\;", "" } },
		{  .printed = "\\\n", .arguments = { "echo", "\\\\;", "" } }
	*/
	};

	return (cr_make_param_array(t_echo_params, test, sizeof(test) / sizeof(t_echo_params)));
}

ParameterizedTest(t_echo_params *params, builtin_echo_suite, echo_valid_args_test)
{
	char *buffer = calloc(200, 1);
	FILE *fp = freopen("echo.test", "w", stdout);

	cr_log_warn("hello\n");
	int return_value = builtin_echo((char **)params->arguments);
	cr_log_warn("hello\n");

	cr_expect_eq(return_value, 0, "Expected echo to return 0, instead got [%d]");

	fclose(fp);
	int fd = open("echo.test", O_RDONLY);
	read(fd, buffer, strlen(params->printed));
	close(fd);

	cr_expect(strcmp(buffer, params->printed) == 0, "Expected echo to print [%s], instead got [%s]", params->printed, buffer);
	free(buffer);
}
