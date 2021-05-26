/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 10:53:54 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/03 11:43:15 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*array_to_list(char **array)
{
	t_list	*head;
	t_list	*node;
	t_dict	*dict;
	int		i;

	if (!array || !*array)
		return (NULL);
	head = NULL;
	dict = NULL;
	i = 0;
	while (array[i])
	{
		dict = env_to_dict(array[i]);
		node = ft_lstnew_safe(dict, free);
		if (!dict || !node)
		{
			free_dict(dict);
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

char	**list_to_array(t_list *list)
{
	char	**array;
	size_t	size;
	int		i;

	i = 0;
	size = ft_lstsize(list);
	array = malloc((size + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (list)
	{
		array[i] = dict_to_env((t_dict *)list->content);
		if (!array[i])
			return (ft_free_matrix((void **)array, i));
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

t_dict	*ft_getenv(const char *name)
{
	t_list	*node;

	node = g_globals->env;
	while (node && name)
	{
		if (!ft_strcmp(((t_dict *)(node->content))->key, name))
			return ((t_dict *)(node->content));
		node = node->next;
	}
	return (NULL);
}

int	ft_setenv(char *name, char *value)
{
	t_list	*node;
	t_dict	*dict;
	char	*new_value;

	new_value = NULL;
	node = NULL;
	dict = ft_getenv(name);
	if (dict)
	{
		if (value)
			new_value = ft_strdup(value);
		if (value && !new_value)
			return (-1);
		free(dict->value);
		dict->value = new_value;
	}
	else
	{
		dict = new_dict(name, value);
		node = ft_lstnew_safe(dict, free_dict);
		if (!dict || !node)
			return (-1);
		ft_lstadd_back(&g_globals->env, node);
	}
	return (0);
}

int	ft_unsetenv(char *name)
{
	t_list	*previous;
	t_list	*node;

	previous = NULL;
	node = g_globals->env;
	while (node)
	{
		if (!ft_strcmp(((t_dict *)(node->content))->key, name))
		{
			if (!previous)
				g_globals->env = node->next;
			else
				previous->next = node->next;
			ft_lstdelone(node, free_dict);
			return (0);
		}
		previous = node;
		node = node->next;
	}
	return (-1);
}
