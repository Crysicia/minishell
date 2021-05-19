/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:35:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/19 16:52:45 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int execute_basic_command(t_list **commands)
{
	char **command;
	int	pid;

	command = command_format(*commands);
	if (!command)
		return (ERR_MALLOC_FAILED);
	pid = fork();
	if (pid == -1)
		printf("ERROR: Could not create child process.\n");
	else if (pid == 0)
		execute_command(command);
	else if (pid > 0)
	{
		g_globals->current_pid = pid;
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		g_globals->current_pid = 0;
	}
	return (SUCCESS);
}
