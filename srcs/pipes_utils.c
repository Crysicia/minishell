/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:56:16 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/10 15:21:42 by lpassera         ###   ########.fr       */
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
