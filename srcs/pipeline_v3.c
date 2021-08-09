/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_v3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:02:45 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/09 16:51:24 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_execute_pipe_command(t_simple_command *cmd, int stdin, int stdout);
void	v2_pipe_child_process_exec(t_simple_command *commands,
								   char **arguments);
void	v2_pipe_parent_process_exec(int to_close);

int	the_pipe_come_again(t_pipeline *pipeline)
{
	t_pipe	*t;
	int	pipe_fd[2];
	int		new_stdin;
	int		new_stdout;
	int		save[2];
	
	t = init_pipeline_utils(pipeline);
	new_stdin = -1;
	new_stdout = -1;
//	pipe_fd[0] = -1;
//	pipe_fd[1] = -1;
	save_in_and_out(&save);
	while (t->scmd_list && t->scmd_list->next)
	{
		pipe(pipe_fd);
		new_stdout = pipe_fd[1];

		
		dprintf(2, "read %d write %d\n", pipe_fd[0], pipe_fd[1]);


		g_globals->pids[++(t->index)] = ft_execute_pipe_command(t->scmd_list->content, new_stdin, new_stdout);
		close(new_stdout);

		new_stdin = pipe_fd[0];
		t->scmd_list = t->scmd_list->next;
	}
	g_globals->pids[++(t->index)] = ft_execute_pipe_command(t->scmd_list->content, new_stdin, -1);
	clean_up_pipeline_utils(t, pipeline);
	restore_in_and_out(&save);
	dprintf(2, "i am not out !\n");
	return (0);
}

int	ft_execute_pipe_command(t_simple_command *cmd, int stdin, int stdout)
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
		
		if (stdin != -1 && dup2(stdin, STDIN_FILENO) != -1 && close(stdin) == -1)
			display_error("big problem in ft_execute_pipe_command", NULL);
		if (stdout != -1 && dup2(stdout, STDOUT_FILENO) != -1 && close(stdout) == -1)
			display_error("other big problem in ft_execute_pipe_command", NULL);

		v2_pipe_child_process_exec(cmd, arguments);

	}

	else
	{
		if (stdin != -1 && close(stdin) == -1)
			display_error("closing error\n", NULL);
			
		v2_pipe_parent_process_exec(stdout);
	}

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

void	v2_pipe_parent_process_exec(int to_close)
{
	dprintf(2, "pipe fd %d\n", to_close);
	if (to_close != -1 && close(to_close) == -1)
		display_error("closing error\n", NULL);
	set_status_code(g_globals->status, false);
}
