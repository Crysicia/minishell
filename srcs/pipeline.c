/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:18:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/19 17:00:15 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int get_pipeline_placement(t_list *commands)
{
	(void)commands;
	return (NOT_IN_PIPELINE);
}

int execute_pipeline(t_pipeline *pipeline)
{
	t_pipes	pipes;

	if (!create_pipes(&pipes))
		return (ERR_PIPE_FAILED);
	execute_pipeline_loop(&pipes, pipeline->commands);
	close_pipes(&pipes);
	return (0);
}

int execute_pipeline_loop(t_pipes *pipes, t_list *commands)
{
	int pid;
	char **command;

	while (commands)
	{
		command = command_format(commands);
		if (!command)
			return (ERR_MALLOC_FAILED);
		pid = execute_pipe(command, pipes, get_pipeline_placement(commands));
		if (pid == -ERR_FORK_FAILED)
			printf("ERROR: Could not create child process.\n");
		else if (pid > 0)
		{
			g_globals->current_pid = pid;
			wait(&g_globals->status);
			set_status_code(g_globals->status, false);
			g_globals->current_pid = 0;
		}
		commands = commands->next;
	}
	return (0);
}

int	execute_pipe(char **command, t_pipes *pipes, int command_flag)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-ERR_FORK_FAILED);
	else if (pid == 0)
	{
		dup_pipes(pipes, command_flag);
		close_pipes(pipes);
		execute_command(command);
	}
	close_relevant_pipes(pipes, command_flag);
	return (pid);
}
