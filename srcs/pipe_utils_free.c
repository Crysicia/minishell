/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:23:35 by lpassera          #+#    #+#             */
/*   Updated: 2021/08/10 12:01:31 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	deallocate_pipe_tab(int **tab, int nb, bool should_close)
{
	int	i;

	i = 0;
	while (i < nb && tab && tab[i])
	{
		if (should_close)
		{
			close(tab[i][0]);
			close(tab[i][1]);
		}
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	*free_pipeline_utils(t_pipe *t, t_pipeline *pipeline)
{
	deallocate_pipe_tab(t->pipe_tab, pipeline->pipe_count, false);
	free(g_globals->pids);
	free(t);
	g_globals->pids = NULL;
	return (NULL);
}
