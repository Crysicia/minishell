/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:56:16 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/03 16:07:11 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int pu_print_error(int code, char *message)
{
	printf("Error: %s: %s\n", message, strerror(errno));
	return (code);
}

int pipes_test(void)
{
	int pipes[2];
	int first_pid;
	int second_pid;

	if (pipe(pipes))
		return (pu_print_error(1, "pipe"));

	first_pid = fork();
	if (first_pid == -1)
		return (pu_print_error(2, "fork"));
	else if (first_pid == 0)
	{
		char *args[] = { "/bin/ls", "-la", NULL};
		dup2(pipes[PIPE_WRITE], STDOUT_FILENO);
		close(pipes[PIPE_READ]);
		close(pipes[PIPE_WRITE]);
		execve("/bin/ls", args, list_to_array(g_globals->env));
	}

	second_pid = fork();
	if (second_pid ==  -1)
		return (pu_print_error(3, "fork"));
	else if (second_pid == 0)
	{
		char *args2[] = { "/usr/bin/head", "-n", "1", NULL};
		dup2(pipes[PIPE_READ], STDIN_FILENO);
		close(pipes[PIPE_READ]);
		close(pipes[PIPE_WRITE]);
		execve("/usr/bin/head", args2, list_to_array(g_globals->env));
	}
	close(pipes[PIPE_READ]);
	close(pipes[PIPE_WRITE]);

	waitpid(first_pid, NULL, 0);
	waitpid(second_pid, NULL, 0);
	return (0);
}