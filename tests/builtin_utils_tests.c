#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

typedef struct	s_display_error_params {
	char result[1024];
	char command[64];
	char custom[256];
}				t_display_error_params;

ParameterizedTestParameters(builtin_utils_suite, display_error_custom_test) {
	static  t_display_error_params display_error_params[] = {
		{ .result = "minishell: pwd: this is a silly error", .command = "pwd", .custom = "this is a silly error" },
		{ .result = "minishell: oopsy: nothing to show here", .command = "oopsy", .custom = "nothing to show here" },
		{ .result = "minishell: : ", .command = "", .custom = "" },
	};

	return cr_make_param_array(t_display_error_params, display_error_params, sizeof(display_error_params) / sizeof(t_display_error_params));
}

ParameterizedTest(t_display_error_params *display_error_params, builtin_utils_suite, display_error_custom_test) {
	char *line = NULL;
	FILE *fp = NULL;
	int fd = 0;
	fp = freopen("display_error.test", "w", stderr);

	display_error(display_error_params->command, display_error_params->custom);
	
	fclose(fp);
	fd = open("display_error.test", O_RDONLY);
	get_next_line(fd, &line);
	close(fd);

	cr_expect_str_eq(line, display_error_params->result,
		"Expected display_error to print [%s], instead got [%s]",
		display_error_params->result, line
	);
	free(line);
}
