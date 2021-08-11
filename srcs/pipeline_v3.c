/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_v3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:02:45 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/11 15:16:44 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	close_in_out(int stdin, int stdout)
{
	if (stdin != -1 && close(stdin) == -1)
		display_error("closing invalid fd on in fd", NULL);
	if (stdout != -1 && close(stdout) == -1)
		display_error("closing invalid fd on out fd", NULL);
}

int	the_pipe_come_again(t_pipeline *pipeline)
{
	t_pipe	*t;
	int		pipe_fd[2];
	int		in;
	int		out;

	t = init_pipeline_utils(pipeline);
	in = STDIN_FILENO;
	out = -1;
	while (t->scmd_list && t->scmd_list->next)
	{
		pipe(pipe_fd);
		out = pipe_fd[1];
		g_globals->pids[++(t->index)] = ft_do_pipe(t->scmd_list->content,
				in, out, pipe_fd[0]);
		close_in_out(in, out);
		in = pipe_fd[0];
		t->scmd_list = t->scmd_list->next;
	}
	g_globals->pids[++(t->index)] = ft_do_pipe(t->scmd_list->content, in, -1, -1);
	close_in_out(in, -1);
	dup2(t->save_stdin, STDIN_FILENO);
	close(t->save_stdin);
	clean_up_pipeline_utils(t, pipeline);
	return (0);
}

int	ft_do_pipe(t_simple_command *cmd, int stdin, int stdout, int to_close)
{
	char	**arguments;
	t_list	*words;
	int		pid;

	words = cmd->words;
	if (words)
		arguments = command_format(words);
	else
		arguments = NULL;
	pid = fork();
	if (pid == -1)
		display_error("while attempting to fork for pipeline", strerror(errno));
	else if (!pid)
	{
		if (to_close != -1)
			close(to_close);
		if (dup2(stdin, STDIN_FILENO) == -1
			|| (stdout != -1 && dup2(stdout, STDOUT_FILENO) == -1))
			display_error("dup error in ft_execute_command", NULL);
		v2_pipe_child_process_exec(cmd, arguments);
	}
	else
		set_status_code(g_globals->status, false);
	ft_free_matrix((void **)arguments, ft_matrix_size((void **)arguments));
	return (pid);
}

void	v2_pipe_child_process_exec(t_simple_command *commands, char **arguments)
{
	char	*path;

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
