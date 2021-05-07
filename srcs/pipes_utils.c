/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:56:16 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/07 18:24:53 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	dup_pipes(t_pipes *pipes, int command_flag)
{
	if (command_flag == FIRST_IN_PIPELINE || command_flag == IN_PIPELINE)
		dup2(pipes->current[PIPE_WRITE], STDOUT_FILENO);
	if (command_flag == IN_PIPELINE || command_flag == LAST_IN_PIPELINE)
		dup2(pipes->previous[PIPE_READ], STDIN_FILENO);
}

void	close_relevant_pipes(t_pipes *pipes, int command_flag)
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

int	execute_pipe(char *path, char **command, t_pipes *pipes, int command_flag)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-ERR_FORK_FAILED);
	else if (pid == 0)
	{
		dup_pipes(pipes, command_flag);
		close_pipes(pipes);
		execve(path, command, list_to_array(g_globals->env));
	}
	close_relevant_pipes(pipes, command_flag);
	return (pid);
}

void	swap_pipes(t_pipes *pipes)
{
	int swap[2];

	ft_memcpy(swap, pipes->previous, 2 * sizeof(int));
	ft_memcpy(pipes->previous, pipes->current, 2 * sizeof(int));
	ft_memcpy(pipes->current, swap, 2 * sizeof(int));
}

void	close_pipes(t_pipes *pipes)
{
	close(pipes->previous[PIPE_READ]);
	close(pipes->previous[PIPE_WRITE]);
	close(pipes->current[PIPE_READ]);
	close(pipes->current[PIPE_WRITE]);
}

bool	create_pipes(t_pipes *pipes)
{

	if (pipe(pipes->previous))
		return (false);
	if (pipe(pipes->current))
	{
		close(pipes->previous[PIPE_READ]);
		close(pipes->previous[PIPE_WRITE]);
		return (false);
	}
	return (true);
}
