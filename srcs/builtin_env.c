/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:09:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/20 15:17:39 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	builtin_env(t_command *command)
{
	t_list	*node;
	char	*env;

	(void) command;
	node = g_globals->env;
	while (node)
	{
		env = dict_to_env(node->content);
		if (((t_dict *)node->content)->value)
			printf("%s\n", env);
		free(env);
		node = node->next;
	}
	return (0);
}
