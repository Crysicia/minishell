#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

typedef struct	s_builtin_unset_params {
	int ret;
	char argument[42];
	char contain_key[42];
	char contain_value[42];
}				t_builtin_unset_params;

ParameterizedTestParameters(builtin_unset_suite, builtin_unset_args_test) {
	static  t_builtin_unset_params builtin_unset_params[] = {
		{ .ret = SUCCESS, .argument = "UNKNOWN" },
		{ .ret = SUCCESS, .argument = "EMPTY" },
		{ .ret = SUCCESS, .argument = "NOTEMPTY" },
		{ .ret = SUCCESS, .argument = "MINI_SHELL" },
		{ .ret = ERR_BUILTIN_FAILED, .argument = "EXISTING=" },
		{ .ret = ERR_BUILTIN_FAILED, .argument = "EXI=STING" },
		{ .ret = ERR_BUILTIN_FAILED, .argument = "=EXISTING" },
		{ .ret = ERR_BUILTIN_FAILED, .argument = "EXIS//TING" },
		{ .ret = ERR_BUILTIN_FAILED, .argument = "1EXISTING" },
		{ .ret = ERR_BUILTIN_FAILED, .argument = "E#XISTING" },
		{ .ret = ERR_BUILTIN_FAILED, .argument = "*EXISTING" },
	};

	return cr_make_param_array(t_builtin_unset_params, builtin_unset_params, sizeof(builtin_unset_params) / sizeof(t_builtin_unset_params));
}

ParameterizedTest(t_builtin_unset_params *builtin_unset_params, builtin_unset_suite, builtin_unset_args_test) {
	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY", "MINI_SHELL=something", NULL };
	t_dict *dict;
	int ret;
	char **array = malloc(2 * sizeof(char *));
	array[0] = builtin_unset_params->argument;
	array[1] = NULL;
	init_globals(envp);
	
	ret = builtin_unset(array);
	dict = ft_getenv(builtin_unset_params->argument);
	if (builtin_unset_params->ret == SUCCESS)
	{
		cr_expect_null(dict,
			"Expected builtin_unset to unset [%s]",
			builtin_unset_params->argument
		);
	}
	cr_expect_eq(ret, builtin_unset_params->ret,
		"Expected builtin_unset to return [%d], instead got [%d], for [%s]",
		builtin_unset_params->ret, ret, builtin_unset_params->argument
	);
	destroy_globals();
}

#define NUM_OF_TESTS 3
Test(builtin_unset_suite, builtin_unset_multiple_args_test) {
	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY", NULL };
	char *arguments[] = { "NOTEMPTY", "EXISTING", "UNKNOWN" };
	t_dict *dict; 
	int ret;
	char **array = malloc((NUM_OF_TESTS + 1) * sizeof(char *));

	for (int i = 0; i < NUM_OF_TESTS; i++) {
		array[i] = arguments[i];
	}
	array[NUM_OF_TESTS] = NULL;

	init_globals(envp);
	
	ret = builtin_unset(array);
	for (int i = 0; i < NUM_OF_TESTS; i++) {
		dict = ft_getenv(arguments[i]);
		cr_expect_null(dict,
			"Expected builtin_unset to unset [%s]",
			arguments[i]
		);
		cr_expect_eq(ret, SUCCESS,
			"Expected builtin_unset to return [%d], instead got [%d], for [%s]",
			SUCCESS, ret, arguments[i]
		);
	}
	destroy_globals();
}

Test(builtin_unset_suite, builtin_unset_multiple_args_fail_test) {
	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY", NULL };
	char *arguments[] = { "NOTEMPTY", "EXIS//TING", "UNKNOWN" };
	int ret;
	char **array = malloc(4 * sizeof(char *));

	for (int i = 0; i < 3; i++) {
		array[i] = arguments[i];
	}
	array[3] = NULL;

	init_globals(envp);
	
	ret = builtin_unset(array);
	cr_expect_null(ft_getenv("NOTEMPTY"), "Expected builtin_unset to unset [%s]", "NOTEMPTY");
	cr_expect(ft_getenv("EXISTING"), "Expected builtin_unset to NOT unset [%s]", "EXISTING");
	cr_expect_null(ft_getenv("UNKNOWN"), "Expected builtin_unset to unset [%s]", "UNKNOWN");
	cr_expect_eq(ret, 1,
		"Expected builtin_unset to return [%d], instead got [%d]",
		1, ret
	);
	destroy_globals();
}
