#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

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
