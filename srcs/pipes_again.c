/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_again.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:19:08 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/05 18:42:51 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_output_pipe(t_simple_command *command);

int	piping_loop(t_pipeline *pipeline)
{
	t_list	*node;

	node = pipeline->commands;
	while (node && node->next)
	{
		init_output_pipe(node->content);
		node = node->next;
	}
	return (0);
}

int	init_output_pipe(t_simple_command *command)
{
	(void)command;
	dprintf(2, "one more pipe\n");
	if (command->redirections)
		dprintf(2, "redirection found\n");
	return (0);
}
