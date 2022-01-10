/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:09:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/08/11 12:22:27 by pcharton         ###   ########.fr       */
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
			ft_putendl_fd(env, 1);
		free(env);
		node = node->next;
	}
	return (SUCCESS);
}
