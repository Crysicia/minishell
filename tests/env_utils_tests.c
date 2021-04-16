#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

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
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	
	char *ret = ft_getenv(ft_getenv_params->argument);
	cr_expect_str_eq(ret, ft_getenv_params->ret, "Expected ft_getenv to return [%s], instead got [%s]", ft_getenv_params->ret, ret);
	destroy_globals();
}
	
Test(env_utils_suite, ft_getenv_null_test) {
	char *envp[] = { "PATH", "PATHA=ko", "PATH=ok", "USER=lpassera", "EMPTY=" };
	init_globals(envp);
	
	char *ret = ft_getenv("UNKNOWN");
	cr_expect_null(ret, "Expected ft_getenv to return NULL, instead got [%s]", ret);
	destroy_globals();
}

Test(env_utils_suite, array_to_list_test) {
	char *argument[] = { "PATH=bonjour", "AAAA=oooo", "OK=KO", "USER-lpassera" };
	t_list *list = array_to_list(argument);
	t_list *head = list;
	int i = 0;
	
	while (list)
	{
		cr_expect(strcmp((char *)list->content, argument[i]) == 0,
				  "Expected array_to_list returned list to contain [%s], instead got [%s], at index [%d]",
				  argument[i], (char *)list->content, i);
		list = list->next;
		i++;
	}
	cr_expect(!list && !argument[i], "Returned list doesn't contain the same number of nodes as the input");
	ft_lstclear(&head, free);
}

Test(env_utils_suite, array_to_list_empty_test) {
	char *argument[] = { "" };
	t_list *list = array_to_list(argument);
	t_list *head = list;
	int i = 0;
	
	while (list)
	{
		cr_expect(strcmp((char *)list->content, argument[i]) == 0,
				  "Expected array_to_list returned list to contain [%s], instead got [%s], at index [%d]",
				  argument[i], (char *)list->content, i);
		list = list->next;
		i++;
	}
	cr_expect(!list && !argument[i], "Returned list doesn't contain the same number of nodes as the input");
	ft_lstclear(&head, free);
}

Test(env_utils_suite, array_to_list_null_test) {
	t_list *list = array_to_list(NULL);

	cr_expect(list == NULL, "Expected array_to_list returned list to contain be NULL");
}

Test(env_utils_suite, list_to_array_test) {
	char *argument[] = { "PATH=bonjour", "AAAA=oooo", "OK=KO", "USER-lpassera" };
	t_list *list;
	t_list *head;
	char **array;
	int i = 0;

	while (argument[i])
	{
		ft_lstadd_back(&list, ft_lstnew(strdup(argument[i])));
		i++;
	}
	head = list;
	array = list_to_array(list);
	i = 0;
	while (array[i])
	{
		cr_expect(strcmp(array[i], argument[i]) == 0,
				  "Expected list_to_array returned array to contain [%s], instead got [%s], at index [%d]",
				  argument[i], array[i], i);
		list = list->next;
		free(array[i]);
		i++;
	}
	cr_expect(!array[i] && !argument[i], "Returned array doesn't contain the same number of nodes as the input");
	free(array[i]);
	free(array);
	ft_lstclear(&head, free);
}

Test(env_utils_suite, list_to_array_empty_test) {
	char *argument[] = { "" };
	t_list *list;
	t_list *head;
	char **array;
	int i = 0;

	while (argument[i])
	{
		ft_lstadd_back(&list, ft_lstnew(strdup(argument[i])));
		i++;
	}
	head = list;
	array = list_to_array(list);
	i = 0;
	while (array[i])
	{
		cr_expect(strcmp(array[i], argument[i]) == 0,
				  "Expected list_to_array returned array to contain [%s], instead got [%s], at index [%d]",
				  argument[i], array[i], i);
		list = list->next;
		free(array[i]);
		i++;
	}
	cr_expect(!array[i] && !argument[i], "Returned array doesn't contain the same number of nodes as the input");
	free(array[i]);
	free(array);
	ft_lstclear(&head, free);
}

Test(env_utils_suite, list_to_array_null_test) {
	char **array = list_to_array(NULL);

	cr_expect(array != NULL, "Expected list_to_array to return an array");
	cr_expect(array[0] == NULL, "Expected list_to_array returned array to be NULL at index 0");
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

// Test(env_utils_suite, ft_setenv_null_test) {
// 	t_list *list = ft_setenv(NULL);

// 	cr_expect(list == NULL, "Expected ft_setenv returned list to contain be NULL");
// }