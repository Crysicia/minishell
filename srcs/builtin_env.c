/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:09:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/19 11:42:41 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	builtin_env(t_command *command)
{
	t_list	*node;
	char	*env;

	if (command->args[1])
		return (127);
	node = g_globals->env;
	while (node)
	{
		env = dict_to_env(node->content);
		printf("%s\n", env);
		free(env);
		node = node->next;
	}
	return (0);
}
