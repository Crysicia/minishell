/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:56:16 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/06 16:10:20 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/pipes.h"

void close_pipes(t_pipes *pipes);

int pu_print_error(int code, char *message)
{
	printf("Error: %s: %s\n", message, strerror(errno));
	return (code);
}

void dup_pipes(t_pipes *pipes, int command_flag)
{
	if (command_flag == FIRST_IN_PIPELINE || command_flag == IN_PIPELINE)
		dup2(pipes->current[PIPE_WRITE], STDOUT_FILENO);
	if (command_flag == IN_PIPELINE || command_flag == LAST_IN_PIPELINE)
		dup2(pipes->previous[PIPE_READ], STDIN_FILENO);
}

void close_relevant_pipes(t_pipes *pipes, int command_flag)
{
	if (command_flag != FIRST_IN_PIPELINE
		&& command_flag != IN_PIPELINE
		&& command_flag != LAST_IN_PIPELINE)
		return ;
	if (command_flag == FIRST_IN_PIPELINE || command_flag == IN_PIPELINE)
		close(pipes->current[PIPE_WRITE]);
	else if (command_flag == LAST_IN_PIPELINE)
		close(pipes->current[PIPE_READ]);
	else
		close(pipes->previous[PIPE_READ]);
}

int execute_pipe(char **command, t_pipes *pipes, int command_flag)
{
	int pid;

	pid = fork();
	if (pid < 0)
		return (pu_print_error(3, "fork")); 
	else if (pid == 0)
	{
		dup_pipes(pipes, command_flag);
		close_pipes(pipes);
		execve(command[0], command, list_to_array(g_globals->env));
	}
	return (pid);
}

void swap_pipes(t_pipes *pipes)
{
	int swap[2];

	ft_memcpy(swap, pipes->previous, 2 * sizeof(int));
	ft_memcpy(pipes->previous, pipes->current, 2 * sizeof(int));
	ft_memcpy(pipes->current, swap, 2 * sizeof(int));
}

void close_pipes(t_pipes *pipes)
{
	close(pipes->previous[PIPE_READ]);
	close(pipes->previous[PIPE_WRITE]);
	close(pipes->current[PIPE_READ]);
	close(pipes->current[PIPE_WRITE]);
}

int pipes_test(void)
{
	t_pipes pipes;

	if (pipe(pipes.previous))
		return (pu_print_error(1, "pipe"));
	if (pipe(pipes.current))
		return (pu_print_error(1, "pipe"));

	char *args[] = { "/bin/ls", "-la", NULL };
	char *args2[] = { "/usr/bin/rev", NULL };
	char *args3[] = { "/usr/bin/head", "-n", "1", NULL };

	int pid1 = execute_pipe(args, &pipes, FIRST_IN_PIPELINE);
	close_relevant_pipes(&pipes, FIRST_IN_PIPELINE);
	waitpid(pid1, NULL, 0);
	swap_pipes(&pipes);
	int pid2 = execute_pipe(args2, &pipes, IN_PIPELINE);
	close_relevant_pipes(&pipes, IN_PIPELINE);
	waitpid(pid2, NULL, 0);
	swap_pipes(&pipes);
	int pid3 = execute_pipe(args3, &pipes, LAST_IN_PIPELINE);
	close_relevant_pipes(&pipes, LAST_IN_PIPELINE);
	waitpid(pid3, NULL, 0);

	close_pipes(&pipes);
	return (0);
}
