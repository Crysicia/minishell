#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

/*
**----------------------------------------------
**-
**-                 FT_SETENV
**-
**----------------------------------------------
*/

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


/*************************************************************************
 * 
 * 						builtin__unset_test
 * 
 * ************************************************************************/

#define NUM_OF_TESTS 3
Test(builtin_unset_suite, builtin_unset_multiple_args_test) {
	char *envp[] = { "EMPTY", "NOTEMPTY=bonjour", "EMPTYSTRING=", "EXISTING=iexist", "EXISTINGEMPTY" };
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


/*************************************************************************
 * 
 * 						builtin_export_test
 * 
 * ************************************************************************/

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
