/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:33:30 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/19 14:29:08 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	init_globals(char *envp[])
{
	g_globals = malloc(sizeof(t_globals));
	if (!g_globals)
		return (false);
	g_globals->current_pid = 0;
	g_globals->status = 0;
	g_globals->env = array_to_list(envp);
	ft_memset(g_globals->last_token, 0, 3);
	if (!g_globals->env && *envp)
		return (destroy_globals());
	return (true);
}

bool	destroy_globals(void)
{
	ft_lstclear(&g_globals->env, free_dict);
	free(g_globals);
	return (false);
}

void	update_last_seen_token(t_token *token)
{
	int		i;
	char	*str;

	if (g_globals && g_globals->last_token
		&& (token->role == operator || token->role == redirection))
	{
		i = 0;
		str = token->cmd;
		while (token->cmd[i])
		{
			g_globals->last_token[i] = token->cmd[i];
			i++;
		}
		while (i < 3)
		{
			g_globals->last_token[i] = 0;
			i++;
		}
	}
	(void)i;
	(void)str;
}
