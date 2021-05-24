/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:18:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/24 12:22:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	get_pipeline_placement(int current, int total)
{
	if (current == 0)
		return (FIRST_IN_PIPELINE);
	if (current == (total - 1))
		return (LAST_IN_PIPELINE);
	return (IN_PIPELINE);
}

int	execute_pipeline(t_pipeline *pipeline)
{
	t_pipes	pipes;
	int		in_and_out[2];
	int		count;

	save_in_and_out(&in_and_out);
	count = pipeline->pipe_count;
	if (!create_pipes(&pipes))
		return (ERR_PIPE_FAILED);
	execute_pipeline_loop(&pipes, pipeline->commands, count);
	close_pipes(&pipes);
	restore_in_and_out(&in_and_out);
	return (0);
}

int	execute_pipeline_loop(t_pipes *pipes, t_list *commands, int pipe_count)
{
	int	error;
	int	current;
	int	placement;

	current = 0;
	while (commands)
	{
		placement = get_pipeline_placement(current, pipe_count);
		if (placement != FIRST_IN_PIPELINE)
			swap_pipes(pipes);
		error = execute_pipe(commands->content, pipes, placement);
		if (error == ERR_FORK_FAILED)
			printf("ERROR: Could not create child process.\n");
		commands = commands->next;
		current++;
	}
	return (0);
}

int	execute_pipe(t_simple_command *command, t_pipes *pipes, int command_flag)
{
	int		pid;
	char	*path;
	char	**arguments;

	pid = fork();
	arguments = command_format(command->words);
	if (!arguments)
		return (ERR_MALLOC_FAILED);
	if (pid < 0)
		return (ERR_FORK_FAILED);
	else if (pid == 0)
	{
		dup_pipes(pipes, command_flag);
		close_pipes(pipes);
		handle_redirections(command->redirections);
		if (is_builtin(arguments[0]))
			exit(execute_builtin(arguments[0], &arguments[1]));
		path = find_exe_path(arguments[0]);
		if (!path)
			return (-1);
		execve(path, arguments, list_to_array(g_globals->env));
		exit(0);
	}
	else
	{
		g_globals->current_pid = pid;
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		g_globals->current_pid = 0;
	}
	close_relevant_pipes(pipes, command_flag);
	return (pid);
}
