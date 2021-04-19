#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

typedef struct	s_env_to_dict_params {
	char key[42];
	char value[42];
	char argument[42];
}				t_env_to_dict_params;

ParameterizedTestParameters(env_utils_suite, env_to_dict_test) {
	static  t_env_to_dict_params env_to_dict_params[] = {
		{ .key = "PATH", .value = "thisisthepath", .argument = "PATH=thisisthepath" },
		{ .key = "USER", .value = "a=b=c=d=e", .argument = "USER=a=b=c=d=e" },
		// { .ret = { .key = "NULL", .value = NULL }, .argument = "NULL=" },
		// { .ret = { .key = "NULL2", .value = NULL }, .argument = "NULL2" },
	};

	return cr_make_param_array(t_env_to_dict_params, env_to_dict_params, sizeof(env_to_dict_params) / sizeof(t_env_to_dict_params));
}

ParameterizedTest(t_env_to_dict_params *env_to_dict_params, env_utils_suite, env_to_dict_test) {
	t_dict *ret = env_to_dict(env_to_dict_params->argument);

	cr_expect_str_eq(ret->key, env_to_dict_params->key, "Expected env_to_dict to return [%s], instead got [%s]", env_to_dict_params->key, ret->key);
	cr_expect_str_eq(ret->value, env_to_dict_params->value, "Expected env_to_dict to return [%s], instead got [%s]", env_to_dict_params->value, ret->value);
}

Test(env_utils_suite, new_dict_test)
{
	t_dict *dict = new_dict("PATH", "there is no path");
	cr_expect_str_eq(dict->key, "PATH");
	cr_expect_str_eq(dict->value, "there is no path");
}
