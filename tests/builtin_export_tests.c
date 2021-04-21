#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

typedef struct	s_builtin_export_params {
	int ret;
	char argument[42];
	char contain[42];
}				t_builtin_export_params;

ParameterizedTestParameters(builtin_export_suite, builtin_export_test) {
	static  t_builtin_export_params builtin_export_params[] = {
		{ .ret = 0, .argument = "PATH" },
		{ .ret = 0, .argument = "USER" },
		{ .ret = 0, .argument = "EMPTY" },
	};

	return cr_make_param_array(t_builtin_export_params, builtin_export_params, sizeof(builtin_export_params) / sizeof(t_builtin_export_params));
}

ParameterizedTest(t_builtin_export_params *builtin_export_params, builtin_export_suite, builtin_export_test) {
	char *envp[] = { "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	
	t_dict *ret = builtin_export(builtin_export_params->argument);
	cr_expect_str_eq(ret->value, builtin_export_params->ret, "Expected builtin_export to return [%s], instead got [%s]", builtin_export_params->ret, ret->value);
	destroy_globals();
}
