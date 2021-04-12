#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

typedef struct	s_is_builtin_params {
	bool ret;
	char *argument;
}				t_is_builtin_params;

ParameterizedTestParameters(exec_builtin_suite, is_builtin_test) {
	static  t_is_builtin_params is_builtin_params[] = {
		{ .ret = true, .argument = "echo" },
		{ .ret = true, .argument = "cd" },
		{ .ret = true, .argument = "exit" },
		{ .ret = true, .argument = "unset" },
		{ .ret = true, .argument = "export" },
		{ .ret = true, .argument = "pwd" },
		{ .ret = true, .argument = "env" },
		{ .ret = false, .argument = "echoo" },
		{ .ret = false, .argument = "" },
		{ .ret = false, .argument = "pwwwd" },
		{ .ret = false, .argument = "ls" },
		{ .ret = false, .argument = "/bin/ls" },
		{ .ret = false, .argument = "set" },
	};

	return cr_make_param_array(t_is_builtin_params, is_builtin_params, sizeof(is_builtin_params) / sizeof(t_is_builtin_params));
}

ParameterizedTest(t_is_builtin_params *is_builtin_params, exec_builtin_suite, is_builtin_test) {
	char og_buffer[6];
	char ret_buffer[6];
	bool ret = is_builtin(is_builtin_params->argument);
	cr_expect(ret == is_builtin_params->ret, "Expected is_builtin to return [%s], instead got [%s]", bool_to_str(og_buffer, is_builtin_params->ret), bool_to_str(ret_buffer, ret));
}
