/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 10:25:57 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/12 06:42:28 by lpassera         ###   ########.fr       */
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
	t->save_stdin = dup(STDIN_FILENO);
	free(g_globals->pids);
	g_globals->pids = ft_calloc(pipeline->pipe_count, sizeof(int));
	if (!g_globals->pids)
		return (free_pipeline_utils(t));
	pipe_node = pipeline->commands;
	while (pipe_node)
	{
		tmp = pipe_node->content;
		look_for_heredoc(tmp->redirections);
		pipe_node = pipe_node->next;
	}
	ft_strlcpy(g_globals->last_token, "|", 2);
	return (t);
}

void	clean_up_pipeline_utils(t_pipe *tmp, t_pipeline *pipeline)
{
	wait_pipeline_end(pipeline->pipe_count);
	if (dup2(tmp->save_stdin, STDIN_FILENO))
		display_error("dup in clean_up_pipe_utils failed", NULL);
	close(tmp->save_stdin);
	free(g_globals->pids);
	free(tmp);
	tmp = NULL;
	g_globals->pids = NULL;
}

void	*free_pipeline_utils(t_pipe *t)
{
	free(g_globals->pids);
	free(t);
	g_globals->pids = NULL;
	return (NULL);
}

int	wait_pipeline_end(int pipe_count)
{
	int	ret;
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		ret = waitpid(g_globals->pids[i], &g_globals->status, 0);
		if (ret == -1)
			return (-1);
		i++;
	}
	wait(&g_globals->status);
	set_status_code(g_globals->status, false);
	return (0);
}
