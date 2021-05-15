/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:40:09 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/15 14:40:09 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/parser.h"

t_pipeline	*new_pipeline(t_simple_command *first)
{
	t_pipeline	*new;

	new = malloc(sizeof(t_pipeline));
	new->commands = ft_lstnew(first);
	if (new && new->commands)
	{
		new->type = pipeline;
		new->pipe_count = 1;
	}
	else
		display_error("Malloc failed", "new_pipeline function");
	return (new);
}

void	free_pipeline(void *to_free)
{
	t_pipeline	*ptr;

	ptr = to_free;
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
	puts(token->cmd);
	printf("lst len %d\n", ft_lstsize(node));
	while (node && node->next)
		node = node->next;
	token = node->content;
	if (token->role == operator && !ft_strncmp(token->cmd, "|", 1))
	{
		command->type = pipeline;
		ft_lstdelone(node, free_token);
		return (1);
	}
	puts("not a pipeline");
	return (0);
}
