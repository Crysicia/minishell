#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

/*
**----------------------------------------------
**-
**-                 FT_GETENV
**-
**----------------------------------------------
*/

typedef struct	s_ft_getenv_params {
	char ret[12];
	char argument[42];
}				t_ft_getenv_params;

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
	
Test(env_utils_suite, ft_getenv_unknown_key_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	
	t_dict *ret = ft_getenv("UNKNOWN");
	cr_expect_null(ret, "Expected ft_getenv to return NULL, instead got [%s]", ret->value);
	destroy_globals();
}
	
Test(env_utils_suite, ft_getenv_null_key_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	
	t_dict *ret = ft_getenv(NULL);
	cr_expect_null(ret, "Expected ft_getenv to return NULL, instead got [%s]", ret->value);
	destroy_globals();
}

/*
**----------------------------------------------
**-
**-               ARRAY_TO_LIST
**-
**----------------------------------------------
*/

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

/*
**----------------------------------------------
**-
**-               LIST_TO_ARRAY
**-
**----------------------------------------------
*/

#define NUM_OF_TESTS 4
Test(env_utils_suite, list_to_array_test) {
	char *argument[] = { "PATH=bonjour", "AAAA=oooo", "OK=KO", "USER=lpassera" };
	t_list *list = array_to_list(argument);
	t_list *head;
	char **array;
	int i;

	head = list;
	array = list_to_array(list);

	for (i = 0; i < NUM_OF_TESTS; i++)
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

/*
**----------------------------------------------
**-
**-                 FT_SETENV
**-
**----------------------------------------------
*/

Test(env_utils_suite, ft_setenv_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_setenv("MINISHELL", "iscool");
	t_dict *env = ft_getenv("MINISHELL");

	cr_expect_str_eq(env->key, "MINISHELL",
		"Expected ft_getenv returned key to be MINISHELL, instead got [%s]",
		env->key);
	cr_expect_str_eq(env->value, "iscool",
		"Expected ft_getenv returned value to be iscool, instead got [%s]",
		env->value);
	cr_expect_eq(ret, 0, "Expected ft_setenv to return 0 on success");
	destroy_globals();
}

Test(env_utils_suite, ft_setenv_empty_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_setenv("MINISHELL", NULL);
	t_dict *env = ft_getenv("MINISHELL");

	cr_expect_str_eq(env->key, "MINISHELL",
		"Expected ft_getenv returned key to be MINISHELL, instead got [%s]",
		env->key);
	cr_expect_null(env->value,
		"Expected ft_getenv returned value to be NULL, instead got [%s]",
		env->value);
	cr_expect_eq(ret, 0, "Expected ft_setenv to return 0 on success");
	destroy_globals();
}

Test(env_utils_suite, ft_setenv_existing_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_setenv("USER", "glados");
	t_dict *env = ft_getenv("USER");

	cr_expect_str_eq(env->key, "USER",
		"Expected ft_getenv returned key to be USER, instead got [%s]",
		env->key);
	cr_expect_str_eq(env->value, "glados",
		"Expected ft_getenv returned value to be glados, instead got [%s]",
		env->value);
	cr_expect_eq(ret, 0, "Expected ft_setenv to return 0 on success");
	destroy_globals();
}

Test(env_utils_suite, ft_setenv_existing_null_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_setenv("USER", NULL);
	t_dict *env = ft_getenv("USER");

	cr_expect_str_eq(env->key, "USER",
		"Expected ft_getenv returned key to be USER, instead got [%s]",
		env->key);
	cr_expect_null(env->value,
		"Expected ft_getenv returned value to be NULL, instead got [%s]",
		env->value);
	cr_expect_eq(ret, 0, "Expected ft_setenv to return 0 on success");
	destroy_globals();
}

Test(env_utils_suite, ft_setenv_null_test) {
	init_globals(NULL);
	int ret = ft_setenv(NULL, NULL);

	cr_expect_null(g_globals->env, "Expected ft_setenv to not add NULL variable");
	cr_expect_eq(ret, -1, "Expected ft_setenv to return -1 on error");
	destroy_globals();
}

/*
**----------------------------------------------
**-
**-                FT_UNSETENV
**-
**----------------------------------------------
*/

Test(env_utils_suite, ft_unsetenv_start_test) {
	char *envp[] = { "PATH", "PATHA=ko", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_unsetenv("PATH");
	t_dict *env = ft_getenv("PATH");

	cr_expect_null(env, "Expected ft_unsetenv to remove PATH");
	cr_expect_not_null(g_globals->env, "Expected env to still have members");
	cr_expect_eq(ret, 0, "Expected ft_unsetenv to return 0 on success");
	destroy_globals();
}

Test(env_utils_suite, ft_unsetenv_middle_test) {
	char *envp[] = { "PATH", "PATHA=ko", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_unsetenv("USER");
	t_dict *env = ft_getenv("USER");

	cr_expect_null(env, "Expected ft_unsetenv to remove USER");
	cr_expect_not_null(g_globals->env, "Expected env to still have members");
	cr_expect_eq(ret, 0, "Expected ft_unsetenv to return 0 on success");
	destroy_globals();
}

Test(env_utils_suite, ft_unsetenv_end_test) {
	char *envp[] = { "PATH", "PATHA=ko", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_unsetenv("EMPTY");
	t_dict *env = ft_getenv("EMPTY");

	cr_expect_null(env, "Expected ft_unsetenv to remove EMPTY");
	cr_expect_not_null(g_globals->env, "Expected env to still have members");
	cr_expect_eq(ret, 0, "Expected ft_unsetenv to return 0 on success");
	destroy_globals();
}

Test(env_utils_suite, ft_unsetenv_unknown_test) {
	char *envp[] = { "PATH", "PATHA=ko", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	int ret = ft_unsetenv("UNKNOWN");
	t_dict *env = ft_getenv("UNKNOWN");

	cr_expect_null(env, "Expected ft_unsetenv to return NULL");
	cr_expect_not_null(g_globals->env, "Expected env to still have members");
	cr_expect_eq(ret, -1, "Expected ft_unsetenv to return -1 on error");
	destroy_globals();
}
