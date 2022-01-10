/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:12:16 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/04 15:14:22 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_simple_command_node(t_simple_command *command)
{
	t_list				*node;
	t_token				*tmp;
	t_redirection		*tmp2;

	printf("printing words list\n");
	node = command->words;
	while (node)
	{
		tmp = node->content;
		printf("[%s]---", tmp->cmd);
		node = node->next;
	}
	printf("\nprinting redirection list\n");
	node = command->redirections;
	while (node)
	{
		tmp2 = node->content;
		printf("[%s] [%s]--", tmp2->operator->cmd, tmp2->file->cmd);
		node = node->next;
	}
	printf("\n");
}

void	print_pipeline(t_pipeline *pipeline)
{
	t_list				*node;
	t_simple_command	*tmp;

	node = pipeline->commands;
	printf("PIPE COUNT == [%d]\n", pipeline->pipe_count);
	while (node)
	{
		tmp = node->content;
		print_simple_command_node(tmp);
		node = node->next;
	}
}

void	print_command_list(t_list *list)
{
	t_list	*node;
	t_block	*command;
	int		i;

	node = list;
	i = 0;
	while (node)
	{
		printf("\nNODE [%d]\n", i++);
		command = node->content;
		if (command->id == simple_command)
			print_simple_command_node(command->kind.cmd);
		else if (command->id == pipeline)
			print_pipeline(command->kind.pipe);
		node = node->next;
	}
}

void	print_command_history(t_dlist *history)
{
	t_dlist	*tmp;

	tmp = history;
	printf("Printing commands history\n");
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->previous;
	}
}
