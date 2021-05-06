/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:56:16 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/05 14:13:31 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
# define IN_PIPELINE 0
# define FIRST_IN_PIPELINE 1
# define LAST_IN_PIPELINE 2

int pu_print_error(int code, char *message)
{
	printf("Error: %s: %s\n", message, strerror(errno));
	return (code);
}

void dup_and_close_pipes(int pipes[2])
{
	dup2(pipes[PIPE_READ], STDIN_FILENO);
	dup2(pipes[PIPE_WRITE], STDOUT_FILENO);
	if (pipes[PIPE_READ] != STDIN_FILENO)
		close(pipes[PIPE_READ]);
	if (pipes[PIPE_WRITE] != STDOUT_FILENO)
		close(pipes[PIPE_WRITE]);
}

void	attribute_pipe_ends(int pipes[2], int command_flag)
{
	if (command_flag == FIRST_IN_PIPELINE)
	{
		close(pipes[PIPE_READ]);
		pipes[PIPE_READ] = STDIN_FILENO;
	}
	else if (command_flag == LAST_IN_PIPELINE)
	{
		close(pipes[PIPE_WRITE]);
		pipes[PIPE_WRITE] = STDOUT_FILENO;
	}
}

int execute_pipe(char **command, int pipes[2], int command_flag)
{
	int pid;

	pid = fork();
	if (pid < 0)
		return (pu_print_error(3, "fork")); 
	else if (pid == 0)
	{
		attribute_pipe_ends(pipes, command_flag);
		dup_and_close_pipes(pipes);
		execve(command[0], command, list_to_array(g_globals->env));
	}
	return (pid);
}

int pipes_test(void)
{
	int pipes[2];
	// int first_pid;
	// int second_pid;

	if (pipe(pipes))
		return (pu_print_error(1, "pipe"));

	// first_pid = fork();
	// if (first_pid == -1)
	// 	return (pu_print_error(2, "fork"));
	// else if (first_pid == 0)
	// {
	// 	char *args[] = { "/bin/ls", "-la", NULL};
	// 	pipes[PIPE_READ] = STDIN_FILENO;
	// 	dup_and_close_pipes(pipes);
	// 	execve("/bin/ls", args, list_to_array(g_globals->env));
	// }

	// second_pid = fork();
	// if (second_pid ==  -1)
	// 	return (pu_print_error(3, "fork"));
	// else if (second_pid == 0)
	// {
	// 	char *args2[] = { "/usr/bin/head", "-n", "1", NULL};
	// 	pipes[PIPE_WRITE] = STDOUT_FILENO;
	// 	dup_and_close_pipes(pipes);
	// 	execve("/usr/bin/head", args2, list_to_array(g_globals->env));
	// }

	char *args[] = { "/bin/ls", "-la", NULL };
	char *args2[] = { "/usr/bin/head", "-n", "1", NULL };
	int pid1 = execute_pipe(args, pipes, FIRST_IN_PIPELINE);
	int pid2 = execute_pipe(args2, pipes, LAST_IN_PIPELINE);
	close(pipes[PIPE_READ]);
	close(pipes[PIPE_WRITE]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

/*	waitpid(first_pid, NULL, 0);
	waitpid(second_pid, NULL, 0);*/
	return (0);
}
