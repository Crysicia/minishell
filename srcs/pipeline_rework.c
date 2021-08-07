/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_rework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 09:25:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/07 14:11:52 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	pipeline_big_loop(t_pipeline *pipeline)
{
	t_pipe	*t;

	t = init_pipeline_utils(pipeline);
	if (!t)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	while (t->scmd_list && t->scmd_list->next)
	{
		pipe(t->pipe_tab[++(t->index)]);
		dprintf(2, "pipe values %d %d\n", t->pipe_tab[t->index][0], t->pipe_tab[t->index][1]);
		g_globals->pids[t->index] = execute_pipe_command(t->pipe_tab[t->index],
				t->scmd_list->content);
		t->scmd_list = t->scmd_list->next;
	}
	dprintf(2, "in %d and out %d\n", t->in_and_out[0], t->in_and_out[1]);
	if (dup2(t->in_and_out[0], STDOUT_FILENO) == -1)
		display_error(strerror(errno), NULL);
	g_globals->pids[t->index] = execute_pipe_command(NULL,
			t->scmd_list->content);
	clean_up_pipeline_utils(t, pipeline);
	return (0);
}

int	execute_pipe_command(int pipe_fd[2], t_simple_command *commands)
{
	char	**arguments;
	t_list	*words;
	int		pid;

	words = commands->words;
	if (words)
		arguments = command_format(words);
	else
		arguments = NULL;
	pid = fork();
	if (pid == -1)
		display_error("while attempting to fork for pipeline",
			strerror(errno));
	else if (!pid)
		pipe_child_process_exec(pipe_fd, commands, arguments);
	else
		pipe_parent_process_exec(pipe_fd);
	ft_free_matrix((void **)arguments, ft_matrix_size((void **)arguments));
	return (pid);
}

void	dup_pipe_stdout(int pipe_fd[2])
{
	if (pipe_fd)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			strerror(errno);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	pipe_child_process_exec(int pipe_fd[2], t_simple_command *commands,
								char **arguments)
{
	char	*path;

	dup_pipe_stdout(pipe_fd);
	if (commands->redirections)
	{
		handle_redirections(commands->redirections);
		apply_all_redirections(commands->redirections);
	}
	if (arguments && is_builtin(arguments[0]))
		exit(set_status_code(execute_builtin(arguments[0], &arguments[1]), 1));
	else if (arguments)
	{
		path = find_exe_path(arguments[0]);
		if (!path)
		{
			display_error(arguments[0], "command not found");
			exit(127);
		}
		else
			execve(path, arguments, list_to_array(g_globals->env));
		exit(1);
	}
	exit(0);
}

void	pipe_parent_process_exec(int pipe_fd[2])
{
	if (pipe_fd)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			display_error(strerror(errno), NULL);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	set_status_code(g_globals->status, false);
}
