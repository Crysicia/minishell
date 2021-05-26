/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:09:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/27 14:40:36 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	builtin_env(char **arguments)
{
	t_list	*node;
	char	*env;

	(void)arguments;
	node = g_globals->env;
	while (node)
	{
		env = dict_to_env(node->content);
		if (((t_dict *)node->content)->value)
			printf("%s\n", env);
		free(env);
		node = node->next;
	}
	return (SUCCESS);
}
