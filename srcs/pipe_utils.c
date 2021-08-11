/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 10:25:57 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/11 14:57:32 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_pipe	*init_pipeline_utils(t_pipeline *pipeline)
{
	t_pipe				*t;
	t_list				*pipe_node;
	t_simple_command	*tmp;

	t = ft_calloc(1, sizeof(t_pipe));
	if (!t)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	t->scmd_list = pipeline->commands;
	t->index = -1;
	dprintf(2, "save_stdin %d\n", t->save_stdin);
	t->save_stdin = dup(STDIN_FILENO);
		dprintf(2, "save_stdin %d\n", t->save_stdin);
	//t->pipe_tab = allocate_pipe_tab(pipeline->pipe_count);
	g_globals->pids = ft_calloc(pipeline->pipe_count, sizeof(int));
	if (!g_globals->pids)
	//	(!t->pipe_tab || 
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
	wait_pipeline_end(pipeline->pipe_count);
//	deallocate_pipe_tab(tmp->pipe_tab, pipeline->pipe_count, true);
	free(g_globals->pids);
	free(tmp);
	tmp = NULL;
	g_globals->pids = NULL;
}

int	**allocate_pipe_tab(int	nb)
{
	int	i;
	int	**tab;

	tab = ft_calloc(nb + 1, sizeof(int *));
	if (tab)
	{
		i = -1;
		while (++i < nb)
		{
			tab[i] = ft_calloc(2, sizeof(int));
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
		dprintf(2, "for process %d exit status is %d\n", ret, g_globals->status);
		if (ret == -1)
			return (-1);
		i++;
	}
	wait(&g_globals->status);
	dprintf(2, "status is %d and i is %d\n", g_globals->status, i);
	set_status_code(g_globals->status, false);
	return (0);
}
