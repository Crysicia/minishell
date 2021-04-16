/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:09:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/15 16:48:29 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	builtin_env(t_command *command)
{
	t_list	*node;

	if (command->args[1])
		return (127);
	node = g_globals->env;
	while (node)
	{
		printf("%s\n", (char *)node->content);
		node = node->next;
	}
	return (0);
}
