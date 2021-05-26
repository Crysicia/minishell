/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:40:09 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:38:43 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "parser.h"

t_pipeline	*new_pipeline(t_simple_command *first)
{
	t_pipeline	*new;

	new = malloc(sizeof(t_pipeline));
	new->commands = ft_lstnew(first);
	if (new && new->commands)
	{
		new->pipe_count = 1;
	}
	else
		display_error("Malloc failed", "new_pipeline function");
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

	if (command->redirections)
		return (0);
	node = command->words;
	token = node->content;
	while (node && node->next)
		node = node->next;
	token = node->content;
	if (token->role == operator && !ft_strncmp(token->cmd, "|", 1))
		return (1);
	return (0);
}
