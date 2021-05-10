/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:18:19 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/10 14:00:42 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int execute_pipeline(t_list **commands)
{
	t_pipes	pipes;

	if (!create_pipes(&pipes))
		return (ERR_PIPE_FAILED);
	pid = execute_pipe(path, command, &pipes, NOT_IN_PIPELINE);
	if (pid == -ERR_FORK_FAILED)
		printf("ERROR: Could not create child process.\n");
	else if (pid > 0)
	{
		g_globals->current_pid = pid;
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		g_globals->current_pid = 0;
	}
}

int execute_pipeline_loop(t_pipes *pipes, )
{

}
