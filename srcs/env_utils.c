/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 10:53:54 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/14 12:50:40 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_list *ft_lstnew_safe(void *content)
{
	t_list *list;

	list = ft_lstnew(content);
	if (!list)
		free(content);
	return (list);
}

t_list *array_to_list(char **array)
{
	t_list *head;
	t_list *node;
	char *dup;
	int i;

	if (!array || !*array)
		return (NULL);
	head = NULL;
	dup = NULL;
	i = 0;
	while (array[i])
	{
		dup = ft_strdup(array[i]);
		if (!dup)
			return (NULL);
		node = ft_lstnew_safe(dup);
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

char **list_to_array(t_list *list)
{
	char **array;
	size_t size;
	int i;

	i = 0;
	size = ft_lstsize(list);
	array = malloc(size * sizeof(char *));
	if (!array)
		return (NULL);
	while (list)
	{
		array[i] = ft_strdup(list->content);
		if (!array[i])
			return (ft_free_matrix((void **)array, i));
		list = list->next;
		i++;
	}
	return (NULL);
}
