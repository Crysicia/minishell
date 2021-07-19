/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_rework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 09:25:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/19 10:18:17 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	pipeline_big_loop(t_pipeline *pipeline)
{
	t_list	*scmd_list;
	int		index;
	int		**pipe_tab;
	int		*pid_tab;
	int		in_and_out[2];

	save_in_and_out(&in_and_out);
	pipe_tab = allocate_pipe_tab(pipeline->pipe_count - 1);
	pid_tab = malloc(sizeof(int) * pipeline->pipe_count - 1);
	if (!pipe_tab || !pid_tab)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	scmd_list = pipeline->commands;
	index = -1;
	while (scmd_list && scmd_list->next)
	{
		pipe(pipe_tab[++index]);
		pid_tab[index] = execute_pipe_command(pipe_tab[index], scmd_list->content);
		dup2(pipe_tab[index][0], STDIN_FILENO);
		scmd_list = scmd_list->next;
	}
	dup2(in_and_out[0], STDOUT_FILENO);
	pid_tab[index] = execute_pipe_command(NULL, scmd_list->content);
	wait_pipeline_end(pipeline->pipe_count - 1, pid_tab);
	deallocate_pipe_tab(pipe_tab, pipeline->pipe_count - 1);
	restore_in_and_out(&in_and_out);
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

int	wait_pipeline_end(int pipe_count, int *pid_tab)
{
	int	ret;
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		ret = waitpid(pid_tab[i], NULL, 0);
		if (ret == -1)
			return (-1);
		i++;
	}
	wait(NULL);
	free(pid_tab);
	return (0);
}
