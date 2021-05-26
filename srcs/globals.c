/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:33:30 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/25 12:55:10 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	destroy_globals(void)
{
	ft_lstclear(&g_globals->env, free);
	ft_dlstclear(&g_globals->history, free);
	free(g_globals);
	return (false);
}

bool	init_globals(char *envp[])
{
	g_globals = malloc(sizeof(t_globals));
	if (!g_globals)
		return (false);
	g_globals->current_pid = 0;
	g_globals->status = 0;
	g_globals->history = NULL;
	g_globals->env = array_to_list(envp);
	if (!g_globals->env && *envp)
		return (destroy_globals());
	return (true);
}
