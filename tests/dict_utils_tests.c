#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

/*
**----------------------------------------------
**-
**-               ENV_TO_DICT
**-
**----------------------------------------------
*/

typedef struct	s_env_to_dict_params {
	char key[42];
	char value[42];
	char argument[42];
}				t_env_to_dict_params;

ParameterizedTestParameters(dict_utils_suite, env_to_dict_test) {
	static  t_env_to_dict_params env_to_dict_params[] = {
		{ .key = "PATH", .value = "thisisthepath", .argument = "PATH=thisisthepath" },
		{ .key = "USER", .value = "a=b=c=d=e", .argument = "USER=a=b=c=d=e" },
		{ .key = "NOVALUE", .value = "", .argument = "NOVALUE=" },
		// { .ret = { .key = "NULL2", .value = NULL }, .argument = "NULL2" },
	};

	return cr_make_param_array(t_env_to_dict_params, env_to_dict_params, sizeof(env_to_dict_params) / sizeof(t_env_to_dict_params));
}

ParameterizedTest(t_env_to_dict_params *env_to_dict_params, dict_utils_suite, env_to_dict_test) {
	t_dict *ret = env_to_dict(env_to_dict_params->argument);

	cr_expect_str_eq(ret->key, env_to_dict_params->key, "Expected env_to_dict to return [%s], instead got [%s]", env_to_dict_params->key, ret->key);
	cr_expect_str_eq(ret->value, env_to_dict_params->value, "Expected env_to_dict to return [%s], instead got [%s]", env_to_dict_params->value, ret->value);
}

Test(dict_utils_suite, env_to_dict_null_value_test)
{
	t_dict *dict = env_to_dict("ENV");
	cr_expect_str_eq(dict->key, "ENV");
	cr_expect_null(dict->value);
}

/*
**----------------------------------------------
**-
**-               DICT_TO_ENV
**-
**----------------------------------------------
*/

typedef struct	s_dict_to_env_params {
	char key[42];
	char value[42];
	char expected[42];
}				t_dict_to_env_params;

ParameterizedTestParameters(dict_utils_suite, dict_to_env_test) {
	static  t_dict_to_env_params dict_to_env_params[] = {
		{ .key = "PATH", .value = "thisisthepath", .expected = "PATH=thisisthepath" },
		{ .key = "USER", .value = "a=b=c=d=e", .expected = "USER=a=b=c=d=e" },
		{ .key = "NOVALUE", .value = "", .expected = "NOVALUE=" },
		// { .ret = { .key = "NULL2", .value = NULL }, .expected = "NULL2" },
	};

	return cr_make_param_array(t_dict_to_env_params, dict_to_env_params, sizeof(dict_to_env_params) / sizeof(t_dict_to_env_params));
}

ParameterizedTest(t_dict_to_env_params *dict_to_env_params, dict_utils_suite, dict_to_env_test) {
	t_dict *dict = new_dict(dict_to_env_params->key, dict_to_env_params->value);
	char *ret = dict_to_env(dict);

	cr_expect_str_eq(ret, dict_to_env_params->expected, "Expected dict_to_env to return [%s], instead got [%s]", dict_to_env_params->expected, ret);
}

Test(dict_utils_suite, dict_to_env_null_value_test)
{
	t_dict *dict = new_dict("ENV", NULL);
	char *ret = dict_to_env(dict);

	cr_expect_str_eq(ret, "ENV");
}

/*
**----------------------------------------------
**-
**-                 NEW_DICT
**-
**----------------------------------------------
*/

Test(dict_utils_suite, new_dict_test)
{
	t_dict *dict = new_dict("PATH", "there is no path");
	cr_expect_str_eq(dict->key, "PATH");
	cr_expect_str_eq(dict->value, "there is no path");
}

Test(dict_utils_suite, new_dict_null_value_test)
{
	t_dict *dict = new_dict("PATH", NULL);
	cr_expect_str_eq(dict->key, "PATH");
	cr_expect_null(dict->value);
}

Test(dict_utils_suite, new_dict_null_key_test)
{
	t_dict *dict = new_dict(NULL, "there is no path");
	cr_expect_null(dict);
}


Test(dict_utils_suite, new_dict_null_test)
{
	t_dict *dict = new_dict(NULL, NULL);
	cr_expect_null(dict);
}
