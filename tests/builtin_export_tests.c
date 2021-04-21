#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>


t_dict *list_dict_search(t_list *list, char *key, char *value)
{
	t_dict *dict;
	while (list)
	{
		dict = list->content;
		if (!strcmp(dict->key, key) && (dict->value == value || !strcmp(dict->value, value)))
			return (dict);
		list = list->next;
	}
	return (NULL);
}

typedef struct	s_builtin_export_params {
	int ret;
	char argument[42];
	char contain_key[42];
	char contain_value[42];
}				t_builtin_export_params;

ParameterizedTestParameters(builtin_export_suite, builtin_export_test) {
	static  t_builtin_export_params builtin_export_params[] = {
		// { .ret = 0, .argument = "PATH", .contain_key = "PATH", .contain_value = NULL },
		{ .ret = 0, .argument = "PATH=", .contain_key = "PATH", .contain_value = "" },
		{ .ret = 0, .argument = "PATH=bonjour", .contain_key = "PATH", .contain_value = "bonjour" },
		{ .ret = 0, .argument = "NOTEMPTY", .contain_key = "NOTEMPTY", .contain_value = "bonjour" },
		{ .ret = 0, .argument = "EMPTY=101", .contain_key = "EMPTY", .contain_value = "101" },
		{ .ret = 0, .argument = "EMPTYSTRING=heyImAString", .contain_key = "EMPTYSTRING", .contain_value = "heyImAString" },
		{ .ret = 0, .argument = "EXISTING=replaced", .contain_key = "EXISTING", .contain_value = "replaced" },
	};

	return cr_make_param_array(t_builtin_export_params, builtin_export_params, sizeof(builtin_export_params) / sizeof(t_builtin_export_params));
}

ParameterizedTest(t_builtin_export_params *builtin_export_params, builtin_export_suite, builtin_export_test) {
	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY" };
	t_dict *dict;
	int ret;
	init_globals(envp);
	
	ret = builtin_export(builtin_export_params->argument);
	dict = ft_getenv(builtin_export_params->contain_key);
	cr_expect_not_null(dict,
		"Expected builtin_export to set [%s]",
		builtin_export_params->contain_key);
	cr_expect_str_eq(dict->value, builtin_export_params->contain_value,
		"Expected builtin_export to set [%s] value to [%s], instead got [%s]",
		builtin_export_params->contain_key,
		builtin_export_params->contain_value,
		dict->value);
	cr_expect_eq(ret, builtin_export_params->ret,
		"Expected builtin_export to return [%d], instead got [%d]",
		builtin_export_params->ret, ret);
	destroy_globals();
}
