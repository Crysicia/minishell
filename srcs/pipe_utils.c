/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 10:25:57 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/09 16:17:06 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pipe	*init_pipeline_utils(t_pipeline *pipeline)
{
	t_pipe				*t;
	t_list				*pipe_node;
	t_simple_command	*tmp;

	t = malloc(sizeof(t_pipe));
	if (!t)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	t->scmd_list = pipeline->commands;
	t->index = -1;
	dprintf(2, "number of pipes == %d\n", pipeline->pipe_count -1);
	t->pipe_tab = allocate_pipe_tab(pipeline->pipe_count - 1);
	g_globals->pids = malloc(sizeof(int) * pipeline->pipe_count - 1);
	if (!t->pipe_tab || !g_globals->pids)
		return (free_pipeline_utils(t, pipeline));
	pipe_node = pipeline->commands;
	while (pipe_node)
	{
		tmp = pipe_node->content;
		look_for_heredoc(tmp->redirections);
		pipe_node = pipe_node->next;
	}
	return (t);
}

void	clean_up_pipeline_utils(t_pipe *tmp, t_pipeline *pipeline)
{
	wait_pipeline_end(pipeline->pipe_count - 1);
	deallocate_pipe_tab(tmp->pipe_tab, pipeline->pipe_count - 1, true);
	free(g_globals->pids);
	free(tmp);
	tmp = NULL;
	g_globals->pids = NULL;
}

int	**allocate_pipe_tab(int	nb)
{
	int	i;
	int	**tab;

	tab = malloc(sizeof(int *) * (nb + 1));
	if (tab)
	{
		i = -1;
		while (++i < nb)
		{
			tab[i] = malloc(sizeof(int) * 2);
			if (!tab[i])
			{
				deallocate_pipe_tab(tab, i, false);
				return (NULL);
			}
		}
		tab[i] = NULL;
	}
	return (tab);
}

int	wait_pipeline_end(int pipe_count)
{
	int	ret;
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		ret = waitpid(g_globals->pids[i], &g_globals->status, 0);
		dprintf(2, "wait return on %d pid %d\n", g_globals->pids[i], ret);
		if (ret == -1)
			return (-1);
		i++;
	}
	wait(&g_globals->status);
	set_status_code(g_globals->status, false);
	return (0);
}
