/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_rework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 09:25:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/09 14:01:56 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	pipeline_big_loop(t_pipeline *pipeline)
{
	t_pipe	*t;
//	int		in_and_out[2];
	int		tmp_stdin;
//	int		tmp_stdout;

	t = init_pipeline_utils(pipeline);
	if (!t)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
//	if (!save_in_and_out(&in_and_out))
//		display_error(strerror(errno), NULL);
	tmp_stdin = dup(STDIN_FILENO);
	dup2(tmp_stdin, STDIN_FILENO);
//	tmp_stdout = dup(STDOUT_FILENO);
	while (t->scmd_list && t->scmd_list->next)
	{
//		if (!save_in_and_out(&in_and_out))
//			display_error(strerror(errno), NULL);
		pipe(t->pipe_tab[++(t->index)]);
		dup2(STDIN_FILENO, t->pipe_tab[t->index][0]);
		g_globals->pids[t->index] = execute_pipe_command(t->pipe_tab[t->index],
				t->scmd_list->content);
//		dup2(tmp_stdin, STDIN_FILENO);
//		if (!restore_in_and_out(&in_and_out))
//			display_error(strerror(errno), NULL);


		dup2(t->pipe_tab[t->index][0], STDIN_FILENO);
		close(t->pipe_tab[t->index][0]);
		close(tmp_stdin);
		t->scmd_list = t->scmd_list->next;
	}

//	save_in_and_out(&in_and_out);

//	if (dup2(in_and_out[0], STDOUT_FILENO) == -1)
//		display_error(strerror(errno), NULL);

//	if (!save_in_and_out(&in_and_out))
//		display_error(strerror(errno), NULL);

	g_globals->pids[t->index] = execute_pipe_command(NULL,
			t->scmd_list->content);
	
	clean_up_pipeline_utils(t, pipeline);
	tmp_stdin = dup(STDIN_FILENO);
	dup2(tmp_stdin, STDIN_FILENO);
	close(tmp_stdin);
//	if (!restore_in_and_out(&in_and_out))
//		display_error(strerror(errno), NULL);
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
		{
			dprintf(2, "burp\n");
			display_error(strerror(errno), NULL);
		}
		int close_wr, close_rd;
		close_wr = close(pipe_fd[1]);
		close_rd = close(pipe_fd[0]);
		if (close_wr)
			dprintf(2, "in child : close_wr failed %s\n", strerror(errno));
		if (close_rd)
			dprintf(2, "in child : close_rd failed %s\n", strerror(errno));
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
		{
			dprintf(2, "bip\n");
			display_error(strerror(errno), NULL);
		}
		close(pipe_fd[1]);
	}
	set_status_code(g_globals->status, false);
}
