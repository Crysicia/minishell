/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:40:09 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/19 11:20:35 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "parser.h"

t_pipeline	*new_pipeline(t_simple_command *first)
{
	t_pipeline	*new;

	new = malloc(sizeof(t_pipeline));
	if (new)
	{
		new->commands = ft_lstnew(first);
		if (new->commands)
			new->pipe_count = 1;
		else
			ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	}
	else
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	return (new);
}

void	free_pipeline(void *to_free)
{
	t_pipeline	*ptr;
	t_list		*list;

	ptr = to_free;
	list = ptr->commands;
	ft_lstclear(&list, free_simple_command);
	free(ptr);
	ptr = NULL;
}

bool	check_if_pipeline(t_simple_command	*command)
{
	t_list	*node;
	t_token	*token;

	node = command->words;
	if (node)
	{
		while (node && node->next)
		{
			node = node->next;
		}
		token = node->content;
		if (token->role == operator && !ft_strncmp(token->cmd, "|", 1))
			return (1);
	}
	return (0);
}
