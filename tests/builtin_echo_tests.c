#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include <sys/stat.h>
#include "helpers.h"

#include <stdio.h>
#include <fcntl.h>

char **tabndup(char tab[10][40], int size)
{
	char **new;
	int	i;

	new = malloc((size + 1) * sizeof(char **));
	if (new)
	{
		i = -1;
		while (++i < size)
		{
			new[i] = strndup(tab[i], strlen(tab[i]));
			if (!new[i])
				return (NULL);
		}
		new[i] = NULL;
	}
	return (new);
}

typedef struct s_echo_params {

	char printed[420];
	int	size;
	char arguments[10][40];
}			t_echo_params;


ParameterizedTestParameters(builtin_echo_suite, echo_valid_args_test) {
	static  t_echo_params test[] = {
		{  .printed = "bonjour\n", .size = 2, .arguments[0] = "bonjour"},
		{  .printed = "bonjour toi\n", .arguments[0] = "bonjour", .arguments[1] = "toi" },
		/*
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

	char **tab = tabndup(params->arguments, params->size);

	int return_value = builtin_echo(tab);


	cr_expect_eq(return_value, 0, "Expected echo to return 0, instead got [%d]");

	fclose(fp);
	int fd = open("echo.test", O_RDONLY);
	read(fd, buffer, 20);
	close(fd);

	cr_expect_eq(strlen(buffer), strlen(params->printed), "Expected echo output len to be [%zu], instead got [%zu]", strlen(params->printed), strlen(buffer));
	cr_expect(strncmp(buffer, params->printed, strlen(buffer)) == 0, "Expected echo to print\n[%s], instead got \n[%s]", params->printed, buffer);
	free(buffer);
}
