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
	static  t_echo_params echo_params[2] = {
		{ .exit_code = 0, .printed = "\n\0", .arguments = { "echo\0" } },
		{ .exit_code = 0, .printed = "bonjour\n\0", .arguments = { "echo\0" } },
	};
	return cr_make_param_array(t_echo_params, echo_params, sizeof(echo_params) / sizeof(*echo_params));
}

ParameterizedTest(t_echo_params *echo_params, builtin_echo_suite, echo_valid_args_test) {
	cr_log_warn("%d", echo_params->exit_code);
	cr_log_warn("%s", echo_params->printed);
	// cr_log_warn("%s", echo_params->arguments[0]);
	// cr_expect(strcmp(params->arguments[0], "echo") == 0, "Good");
	// cr_free(echo_params);
}

// Test(builtin_echo_suite, echo_valid_args_test) {
// // 	char *envp[] = { "BONJOUR=test", "USER=pcharton", "TEST=test", "ANOTHER=brickinthewall", NULL };
// // 	char *line = NULL;
// // 	FILE *fp = NULL;
// // 	int fd = 0;

// // 	fp = freopen("env.test", "w", stdout);
// 	cr_expect(0 == 0, "Expect builtin_env to return 0 without any argument");
// // 	fclose(fp);
// // 	fd = open("env.test", O_RDONLY);
// // 	for (int i = 0; i < 4; i++)
// // 	{
// // 		get_next_line(fd, &line);
// //  	    cr_expect(strcmp(envp[i], line) == 0,  "Expect printed strings to be the same");
// // 	    cr_free(line);
// // 	}
// // 	close(fd);
// }
