/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:50:15 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/22 14:36:34 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	mock_free(void *pointer)
{
	(void)pointer;
}

int	dict_key_cmp(void *dict1, void *dict2)
{
	if (!dict1 || !dict2)
		return (0);
	return (ft_strcmp(((t_dict *)dict1)->key, ((t_dict *)dict2)->key));
}

// NEED TO USE LSTMAP
t_list	*list_dup(t_list *list)
{
	t_list	*new_list;
	t_list	*node;

	new_list = NULL;
	while (list)
	{
		node = ft_lstnew(list->content);
		if (!node)
		{
			ft_lstclear(&new_list, mock_free);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		list = list->next;
	}
	return (new_list);
}

int	display_export(void)
{
	t_list	*list;

	list = list_dup(g_globals->env);
	ft_lstsort(&list, dict_key_cmp);
	while (list)
	{
		printf("export %s", ((t_dict *)list->content)->key);
		if (((t_dict *)list->content)->value)
			printf("=\"%s\"", ((t_dict *)list->content)->value);
		printf("\n");
		list = list->next;
	}
	ft_lstclear(&list, mock_free);
	return (0);
}

int	builtin_export(char *argument)
{
	t_dict	*dict;
	t_dict	*env;
	int		ret;

	ret = 0;
	if (!argument)
		return (display_export());
	dict = env_to_dict(argument);
	if (!dict)
		return (-1);
	env = ft_getenv(dict->key);
	if (env && (env->value && !dict->value))
		;
	else if (ft_setenv(dict->key, dict->value))
		ret = -1;
	free_dict(dict);
	return (ret);
}
