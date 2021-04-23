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

ParameterizedTestParameters(builtin_export_suite, builtin_export_args_test) {
	static  t_builtin_export_params builtin_export_params[] = {
		// { .ret = 0, .argument = "PATH", .contain_key = "PATH", .contain_value = NULL },
		{ .ret = 0, .argument = "PATH=", .contain_key = "PATH", .contain_value = "" },
		{ .ret = 0, .argument = "PATH2=", .contain_key = "PATH2", .contain_value = "" },
		{ .ret = 0, .argument = "PATH=bonjour", .contain_key = "PATH", .contain_value = "bonjour" },
		{ .ret = 0, .argument = "NOTEMPTY", .contain_key = "NOTEMPTY", .contain_value = "bonjour" },
		{ .ret = 0, .argument = "EMPTY=101", .contain_key = "EMPTY", .contain_value = "101" },
		{ .ret = 0, .argument = "EMPTYSTRING=heyImAString", .contain_key = "EMPTYSTRING", .contain_value = "heyImAString" },
		{ .ret = 0, .argument = "EXISTING=replaced", .contain_key = "EXISTING", .contain_value = "replaced" },
		{ .ret = 1, .argument = "EXIS//TING=replaced", .contain_key = "EXISTING", .contain_value = "iexist" },
		{ .ret = 1, .argument = "1EXISTING=replaced", .contain_key = "EXISTING", .contain_value = "iexist" },
		{ .ret = 1, .argument = "E#XISTING=replaced", .contain_key = "EXISTING", .contain_value = "iexist" },
		{ .ret = 1, .argument = "*EXISTING=replaced", .contain_key = "EXISTING", .contain_value = "iexist" },
	};

	return cr_make_param_array(t_builtin_export_params, builtin_export_params, sizeof(builtin_export_params) / sizeof(t_builtin_export_params));
}

ParameterizedTest(t_builtin_export_params *builtin_export_params, builtin_export_suite, builtin_export_args_test) {
	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY" };
	t_dict *dict;
	int ret;
	char **array = malloc(2 * sizeof(char *));
	array[0] = builtin_export_params->argument;
	array[1] = NULL;
	init_globals(envp);
	
	ret = builtin_export(array);
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
		"Expected builtin_export to return [%d], instead got [%d] (Arg: %s, Expected key: %s, Expected value: %s)",
		builtin_export_params->ret, ret, builtin_export_params->argument, builtin_export_params->contain_key, builtin_export_params->contain_value);
	destroy_globals();
}

#define NUM_OF_TESTS 6
Test(builtin_export_suite, builtin_export_no_args_test) {
	char *envp[] = { "BONJOUR=test", "LOL=", "USER=pcharton", "TEST=test", "NOPE", "ANOTHER=brickinthewall" };
	char *output[] = { "export ANOTHER=\"brickinthewall\"", "export BONJOUR=\"test\"", "export LOL=\"\"", "export NOPE", "export TEST=\"test\"", "export USER=\"pcharton\"" };
	init_globals(envp);

	char *line = NULL;
	FILE *fp = NULL;
	int fd = 0;

	fp = freopen("export.test", "w", stdout);
	cr_expect(builtin_export(NULL) == 0, "Expect builtin_export to return 0 without any argument");
	fclose(fp);
	fd = open("export.test", O_RDONLY);
	for (int i = 0; i < NUM_OF_TESTS; i++)
	{
		get_next_line(fd, &line);
 	    cr_expect_str_eq(output[i], line,  "Expect printed strings to be the same, expected [%s], got [%s]", output[i], line);
	    cr_free(line);
	}
	close(fd);
	destroy_globals();
}

#define NUM_OF_TESTS 4
Test(builtin_export_suite, builtin_export_multiple_args_test) {
	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY" };
	char *arguments[] = { "NOTEMPTY", "EXISTING=", "PATH=test", "OOPS===loool" };
	char *arguments_keys[] = { "NOTEMPTY", "EXISTING", "PATH", "OOPS" };
	char *arguments_values[] = { "bonjour", "", "test", "==loool" };
	t_dict *dict; 
	int ret;
	char **array = malloc(5 * sizeof(char *));

	for (int i = 0; i < NUM_OF_TESTS; i++) {
		array[i] = arguments[i];
	}
	array[NUM_OF_TESTS] = NULL;

	init_globals(envp);
	
	ret = builtin_export(array);
	for (int i = 0; i < NUM_OF_TESTS; i++) {
		dict = ft_getenv(arguments_keys[i]);
		cr_expect_not_null(dict,
			"Expected builtin_export to set [%s]",
			arguments_keys[i]);
		cr_expect_str_eq(dict->value, arguments_values[i],
			"Expected builtin_export to set [%s] value to [%s], instead got [%s]",
			arguments_keys[i],
			arguments_values[i],
			dict->value);
		cr_expect_eq(ret, 0,
			"Expected builtin_export to return [%d], instead got [%d] (Arg: %s, Expected key: %s, Expected value: %s)",
			0, ret, arguments[i], arguments_keys[i], arguments_values[i]);
	}
	destroy_globals();
}

// #define NUM_OF_TESTS 4
// Test(builtin_export_suite, builtin_export_multiple_args_error_test) {
// 	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY" };
// 	char *arguments[] = { "NOTEMPTY", "EXISTING=", "PATH=test", "OOPS===loool" };
// 	char *arguments_keys[] = { "3NOTEMPTY", "EXISTING", "PATH", "OOPS" };
// 	char *arguments_values[] = { "bonjour", "", "test", "==loool" };
// 	t_dict *dict; 
// 	int ret;
// 	char **array = malloc(5 * sizeof(char *));

// 	for (int i = 0; i < NUM_OF_TESTS; i++) {
// 		array[i] = arguments[i];
// 	}
// 	array[NUM_OF_TESTS] = NULL;

// 	init_globals(envp);
	
// 	ret = builtin_export(array);
// 	for (int i = 0; i < NUM_OF_TESTS; i++) {
// 		dict = ft_getenv(arguments_keys[i]);
// 		cr_expect_not_null(dict,
// 			"Expected builtin_export to set [%s]",
// 			arguments_keys[i]);
// 		cr_expect_str_eq(dict->value, arguments_values[i],
// 			"Expected builtin_export to set [%s] value to [%s], instead got [%s]",
// 			arguments_keys[i],
// 			arguments_values[i],
// 			dict->value);
// 		cr_expect_eq(ret, 0,
// 			"Expected builtin_export to return [%d], instead got [%d] (Arg: %s, Expected key: %s, Expected value: %s)",
// 			0, ret, arguments[i], arguments_keys[i], arguments_values[i]);
// 	}
// 	destroy_globals();
// }
