/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_rework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 09:25:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/28 11:48:11 by lpassera         ###   ########.fr       */
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
		g_globals->pids[t->index] = execute_pipe_command(t->pipe_tab[t->index],
				t->scmd_list->content);
		dup2(t->pipe_tab[t->index][0], STDIN_FILENO);
		t->scmd_list = t->scmd_list->next;
	}
	dup2(t->in_and_out[0], STDOUT_FILENO);
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
		pipe_parent_process_exec(pipe_fd, pid);
	ft_free_matrix((void **)arguments, ft_matrix_size((void **)arguments));
	return (pid);
}

void	pipe_child_process_exec(int pipe_fd[2], t_simple_command *commands,
								char **arguments)
{
	char	*path;

	if (pipe_fd)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
	}
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
			display_error(arguments[0], "command not found");
		else
			execve(path, arguments, list_to_array(g_globals->env));
		exit(1);
	}
	exit(0);
}

void	pipe_parent_process_exec(int pipe_fd[2], int fork_ret)
{
	if (pipe_fd)
		close(pipe_fd[1]);
	set_status_code(g_globals->status, false);
}
