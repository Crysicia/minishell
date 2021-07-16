/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_rework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 09:25:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/16 17:22:20 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	pipeline_big_loop(t_pipeline *pipeline)
{
	t_list				*scmd_list;
	int					index;
	int					**pipe_tab;
	int					in_and_out[2];

	save_in_and_out(&in_and_out);
	index = -1;
	pipe_tab = allocate_pipe_tab(pipeline->pipe_count - 1);
	if (!pipe_tab)
		ft_exit();
	scmd_list = pipeline->commands;
	while (scmd_list && scmd_list->next)
	{
		pipe(pipe_tab[++index]);
		execute_pipe_command(pipe_tab[index], scmd_list->content);
		dup2(pipe_tab[index][0], STDIN_FILENO);
		scmd_list = scmd_list->next;
	}
	dup2(in_and_out[0], STDOUT_FILENO);
	execute_pipe_command(NULL, scmd_list->content);
	wait_pipeline_end(pipeline->pipe_count - 1);
	deallocate_pipe_tab(pipe_tab, pipeline->pipe_count - 1);
	restore_in_and_out(&in_and_out);
	return (0);
}

int	execute_pipe_command(int pipe_fd[2], t_simple_command *commands)
{
	char	**arguments;
	t_list	*words;
	int		fork_ret;

	words = commands->words;
	if (words)
		arguments = command_format(words);
	else
		arguments = NULL;
	fork_ret = fork();
	if (fork_ret == -1)
		display_error("while attempting to fork for pipeline",
					  strerror(errno));
	else if (!fork_ret)
		pipe_child_process_exec(pipe_fd, commands, arguments);
	else
		pipe_parent_process_exec(pipe_fd, fork_ret);
	ft_free_matrix((void **)arguments, ft_matrix_size((void **)arguments));
	return (0);
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
	if (!arguments)
		exit(0);
	if (arguments && is_builtin(arguments[0]))
		exit(set_status_code(execute_builtin(arguments[0], &arguments[1]), true));
	else if (arguments)
	{
		path = find_exe_path(arguments[0]);
		if (!path)
			display_error(arguments[0], "command not found");
		execve(path, arguments, list_to_array(g_globals->env));
		exit(1);
	}
}

void	pipe_parent_process_exec(int pipe_fd[2], int fork_ret)
{
	if (pipe_fd)
		close(pipe_fd[1]);
	g_globals->current_pid = fork_ret;
	set_status_code(g_globals->status, false);
	g_globals->current_pid = 0;
}

int	wait_pipeline_end(int pipe_count)
{
	int	ret;
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		ret = waitpid(-1, NULL, 0);
		if (ret == -1)
			return (-1);
		i++;
	}
	wait(NULL);
	return (0);
}
