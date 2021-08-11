/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_pids.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:29:49 by lpassera          #+#    #+#             */
/*   Updated: 2021/08/11 16:36:38 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_pid_to_global(int pid)
{
	int	i;
	int	j;
	int	*tmp;

	i = 0;
	j = 0;
	while (g_globals->pids && g_globals->pids[i])
		i++;
	tmp = malloc(sizeof(int) * (i + 2));
	if (!tmp)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);

	while (j < i)
	{
		tmp[j] = g_globals->pids[j];
		j++;
	}
	tmp[j] = pid;
	tmp[j + 1] = 0;
	free(g_globals->pids);
	g_globals->pids = tmp;
}

void	reset_pids_from_global(void)
{
	free(g_globals->pids);
	g_globals->pids = malloc(sizeof(int));
	if (!g_globals->pids)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	g_globals->pids[0] = 0;
}
