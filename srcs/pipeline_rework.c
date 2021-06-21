/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_rework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 09:25:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/06/20 09:25:29 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
		handle_redirections(commands->redirections);
	if (is_builtin(arguments[0]))
	{
		set_status_code(execute_builtin(arguments[0], &arguments[1]), true);
		exit(0);
	}
	else
	{
		path = find_exe_path(arguments[0]);
		if (!path)
			return ;
		execve(path, arguments, list_to_array(g_globals->env));
	}
}

void	pipe_parent_process_exec(int pipe_fd[2], int (*in_and_out)[],
		int fork_ret)
{
	if (pipe_fd)
		close(pipe_fd[1]);
	g_globals->current_pid = fork_ret;
	set_status_code(g_globals->status, false);
	g_globals->current_pid = 0;
	restore_in_and_out(in_and_out);
}

int	execute_pipe_command(int pipe_fd[2], t_simple_command *commands)
{
	char	**arguments;
	t_list	*words;
	int		fork_ret;
	int		in_and_out[2];
	char	*path;

	words = commands->words;
	arguments = command_format(words);
	save_in_and_out(&in_and_out);
	path = find_exe_path(arguments[0]);
	if (path)
	{		
		fork_ret = fork();
		if (fork_ret == -1)
			display_error("while attempting to fork for pipeline",
				strerror(errno));
		else if (!fork_ret)
			pipe_child_process_exec(pipe_fd, commands, arguments);
		else
			pipe_parent_process_exec(pipe_fd, &in_and_out, fork_ret);
	}
	else
		printf("-Minishell: %s: command not found\n", arguments[0]);
	ft_free_matrix((void **)arguments, ft_matrix_size((void **)arguments));
	free(path);
	return (0);
}

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
	execute_single_command(scmd_list->content);
	wait_pipeline_end(pipeline->pipe_count - 1);
	deallocate_pipe_tab(pipe_tab, pipeline->pipe_count - 1);
	restore_in_and_out(&in_and_out);
	wait(NULL);
	return (0);
}

int	wait_pipeline_end(int pipe_count)
{
	int	ret;
	int	i;

	i = 0;
	while (i < pipe_count - 1)
	{
		ret = waitpid(-1, NULL, 0);
		if (ret == -1)
		{
			display_error("while waiting pipeline to end", strerror(errno));
			return (-1);
		}
		i++;
	}
	return (0);
}
