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

# define IN_PIPELINE 0
# define FIRST_IN_PIPELINE 1
# define LAST_IN_PIPELINE 2

typedef struct	s_pipes {
	int			previous[2];
	int			current[2];
}				t_pipes;
void close_pipes(t_pipes *pipes);

int pu_print_error(int code, char *message)
{
	printf("Error: %s: %s\n", message, strerror(errno));
	return (code);
}

void dup_and_close_pipes(t_pipes *pipes, int command_flag)
{
	if (command_flag == FIRST_IN_PIPELINE || command_flag == IN_PIPELINE)
		dup2(pipes->current[PIPE_WRITE], STDOUT_FILENO);
	dup2(pipes->previous[PIPE_READ], STDIN_FILENO);
	close_pipes(pipes);
}

// void	attribute_pipe_ends(int pipes[2], int command_flag)
// {
// 	// int swap;

// 	if (command_flag == FIRST_IN_PIPELINE)
// 	{
// 		close(pipes[PIPE_READ]);	
// 		pipes[PIPE_READ] = STDIN_FILENO;
// 	}
// 	else if (command_flag == LAST_IN_PIPELINE)
// 	{
// 		close(pipes[PIPE_WRITE]);
// 		pipes[PIPE_WRITE] = STDOUT_FILENO;
// 	}
// 	// else
// 	// {
// 	// 	swap = pipes[PIPE_WRITE];
// 	// 	pipes[PIPE_WRITE] = pipes[PIPE_READ];
// 	// 	pipes[PIPE_READ] = swap;
// 	// }
// }

void close_relevant_pipes(t_pipes *pipes, int command_flag)
{
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
		// printf("\nENDS --\nREAD: %d, WRITE: %d\n", pipes[PIPE_READ], pipes[PIPE_WRITE]);
		// attribute_pipe_ends(pipes, command_flag);
		// printf("TO DUP --\nREAD: %d, WRITE: %d\n", pipes[PIPE_READ], pipes[PIPE_WRITE]);
		// fflush(stdout);
		dup_and_close_pipes(pipes, command_flag);
		execve(command[0], command, list_to_array(g_globals->env));
	}
	return (pid);
}

void print_pipes(t_pipes *pipes)
{
	printf("[Previous pipe] - READ: %d, WRITE: %d\n", pipes->previous[PIPE_READ], pipes->previous[PIPE_WRITE]);
	printf("[Current pipe] - READ: %d, WRITE: %d\n\n", pipes->current[PIPE_READ], pipes->current[PIPE_WRITE]);
	fflush(stdout);
}

void swap_pipes(t_pipes *pipes)
{
	int swap[2];

	// print_pipes(pipes);
	// ft_memcpy(swap, pipes->previous, 2);
	// ft_memcpy(pipes->previous, pipes->current, 2);
	// ft_memcpy(pipes->current, swap, 2);

	swap[PIPE_READ] = pipes->previous[PIPE_READ];
	swap[PIPE_WRITE] = pipes->previous[PIPE_WRITE];

	pipes->previous[PIPE_READ] = pipes->current[PIPE_READ];
	pipes->previous[PIPE_WRITE] = pipes->current[PIPE_WRITE];

	pipes->current[PIPE_READ] = swap[PIPE_READ];
	pipes->current[PIPE_WRITE] = swap[PIPE_WRITE];
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
	// int pipes[2];
	t_pipes pipes;


	// int first_pid;
	// int second_pid;

	if (pipe(pipes.previous))
		return (pu_print_error(1, "pipe"));
	if (pipe(pipes.current))
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
	// execute_pipe(NULL, &pipes, LAST_IN_PIPELINE);
	// swap_pipes(&pipes);

	(void)pid1;
	(void)pid2;
	(void)pid3;

	close_pipes(&pipes);


/*	waitpid(first_pid, NULL, 0);
	waitpid(second_pid, NULL, 0);*/
	return (0);
}
