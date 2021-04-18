#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

typedef struct	s_ft_getenv_params {
	char ret[12];
	char argument[42];
}				t_ft_getenv_params;

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

ParameterizedTestParameters(env_utils_suite, ft_getenv_test) {
	static  t_ft_getenv_params ft_getenv_params[] = {
		{ .ret = "ok", .argument = "PATH" },
		{ .ret = "lpassera", .argument = "USER" },
		{ .ret = "", .argument = "EMPTY" },
	};

	return cr_make_param_array(t_ft_getenv_params, ft_getenv_params, sizeof(ft_getenv_params) / sizeof(t_ft_getenv_params));
}

ParameterizedTest(t_ft_getenv_params *ft_getenv_params, env_utils_suite, ft_getenv_test) {
	char *envp[] = { "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	
	t_dict *ret = ft_getenv(ft_getenv_params->argument);
	cr_expect_str_eq(ret->value, ft_getenv_params->ret, "Expected ft_getenv to return [%s], instead got [%s]", ft_getenv_params->ret, ret->value);
	destroy_globals();
}
	
Test(env_utils_suite, ft_getenv_null_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	
	t_dict *ret = ft_getenv("UNKNOWN");
	cr_expect_null(ret, "Expected ft_getenv to return NULL, instead got [%s]", ret->value);
	destroy_globals();
}

Test(env_utils_suite, array_to_list_test) {
	char *argument[] = { "PATH=bonjour", "AAAA=oooo", "OK=KO", "USER=lpassera", "TOOMUCHEQ=a=b=c=d=e" };
	t_dict expected[] = {
							{ .key = "PATH", .value = "bonjour" },
						   	{ .key = "AAAA", .value = "oooo" },
						  	{ .key = "OK", .value = "KO" },
						  	{ .key = "USER", .value = "lpassera" },
						   	{ .key = "TOOMUCHEQ", .value = "a=b=c=d=e" },
						};
	t_list *list = array_to_list(argument);
	t_list *head = list;
	int i = 0;
	
	while (list)
	{
		cr_expect_str_eq(((t_dict *)(list->content))->key, expected[i].key,
				  "Expected array_to_list returned list to contain [%s], instead got [%s], at index [%d]",
				  expected[i].key, ((t_dict *)(list->content))->key, i);
		cr_expect_str_eq(((t_dict *)(list->content))->value, expected[i].value,
				  "Expected array_to_list returned list to contain [%s], instead got [%s], at index [%d]",
				  expected[i].value, ((t_dict *)(list->content))->value, i);
		list = list->next;
		i++;
	}
	cr_expect(!list && !argument[i], "Returned list doesn't contain the same number of nodes as the input");
	ft_lstclear(&head, free);
}

Test(env_utils_suite, array_to_list_empty_test) {
	char *argument[] = { "" };
	t_list *list = array_to_list(argument);

	cr_expect_str_empty(((t_dict *)(list->content))->key,
		"Expected array_to_list returned list to be empty, instead got [%s]",
		((t_dict *)(list->content))->key);
	cr_expect_null(((t_dict *)(list->content))->value,
		"Expected array_to_list returned list value to be NULL, instead got [%s]",
		((t_dict *)(list->content))->value);
	ft_lstclear(&list, free);
}

Test(env_utils_suite, array_to_list_null_value_test) {
	char *argument[] = { "PATH" };
	t_list *list = array_to_list(argument);

	cr_expect_str_eq(((t_dict *)(list->content))->key, "PATH",
		"Expected array_to_list returned list to be PATH, instead got [%s]",
		((t_dict *)(list->content))->key);
	cr_expect_null(((t_dict *)(list->content))->value,
		"Expected array_to_list returned list value to be NULL, instead got [%s]",
		((t_dict *)(list->content))->value);
	ft_lstclear(&list, free);
}

Test(env_utils_suite, array_to_list_null_test) {
	t_list *list = array_to_list(NULL);

	cr_expect_null(list, "Expected array_to_list returned list to be NULL");
}

Test(env_utils_suite, new_dict_test)
{
	t_dict *dict = new_dict("PATH", "there is no path");
	cr_expect_str_eq(dict->key, "PATH");
	cr_expect_str_eq(dict->value, "there is no path");
}

Test(env_utils_suite, list_to_array_test) {
	char *argument[] = { "PATH=bonjour", "AAAA=oooo", "OK=KO", "USER=lpassera" };
	t_list *list = array_to_list(argument);
	t_list *head;
	char **array;
	int i;

	head = list;
	array = list_to_array(list);

	for (i = 0; array[i]; i++)
	{
		cr_expect_str_eq(array[i], argument[i],
				  "Expected list_to_array returned array to contain [%s], instead got [%s], at index [%d]",
				  argument[i], array[i], i);
		list = list->next;
		free(array[i]);
	}
	cr_expect(!array[i] && !argument[i], "Returned array doesn't contain the same number of nodes as the input");
	free(array[i]);
	free(array);
	ft_lstclear(&head, free);
}

Test(env_utils_suite, list_to_array_null_test) {
	char **array = list_to_array(NULL);

	cr_expect(array != NULL, "Expected list_to_array to return an array");
	cr_expect_null(array[0], "Expected list_to_array returned array to be NULL at index 0");
	free(array[0]);
	free(array);
}

// Test(env_utils_suite, ft_setenv_test) {
// 	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
// 	init_globals(envp);
// 	int ret = ft_setenv("MINISHELL", "iscool");
// 	t_list *head = list;
// 	int i = 0;
	
// 	while (list)
// 	{
// 		cr_expect(strcmp((char *)list->content, argument[i]) == 0,
// 				  "Expected ft_setenv returned list to contain [%s], instead got [%s], at index [%d]",
// 				  argument[i], (char *)list->content, i);
// 		list = list->next;
// 		i++;
// 	}
// 	cr_expect(!list && !argument[i], "Returned list doesn't contain the same number of nodes as the input");
// 	ft_lstclear(&head, free);
// }

// Test(env_utils_suite, ft_setenv_empty_test) {
// 	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
// 	init_globals(envp);
// 	int ret = ft_setenv(argument);
// 	t_list *head = list;
// 	int i = 0;
	
// 	while (list)
// 	{
// 		cr_expect(strcmp((char *)list->content, argument[i]) == 0,
// 				  "Expected ft_setenv returned list to contain [%s], instead got [%s], at index [%d]",
// 				  argument[i], (char *)list->content, i);
// 		list = list->next;
// 		i++;
// 	}
// 	cr_expect(!list && !argument[i], "Returned list doesn't contain the same number of nodes as the input");
// 	ft_lstclear(&head, free);
// }

Test(env_utils_suite, ft_setenv_null_test) {
	init_globals(NULL);
	int ret = ft_setenv(NULL, NULL);

	cr_expect_null(g_globals->env, "Expected ft_setenv to not add NULL variable");
	cr_expect_eq(ret, -1, "Expected ft_setenv to return -1 on error");
	destroy_globals();
}
