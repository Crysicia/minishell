/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:35:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/14 14:14:56 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int create_file(char *path, char *redirection_type)
{
	int fd;
	int open_flags;

	open_flags = O_RDWR;
	if (ft_strcmp(redirection_type, "<"))
		open_flags |= O_CREAT;
	if (!ft_strcmp(redirection_type, ">>"))
		open_flags |= O_APPEND;
	fd = open(path, open_flags, 0644);
	return (fd);
}

void apply_redirection(char *path, char *redirection_type)
{
	int fd;

	fd = create_file(path, redirection_type);
	if (fd == -1)
	{
		display_error(path, strerror(errno));
		exit(1);
	}
	if (!ft_strcmp(redirection_type, "<"))
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

int test_redirections(void)
{
	int pid;
	char *argv[] = { "/bin/cat", NULL };

	pid = fork();
	if (pid == 0)
	{
		apply_redirection("Makefile", "<");
		apply_redirection("main.c", "<");
		apply_redirection("out", ">");
		apply_redirection("out2", ">");
		apply_redirection("out3", ">>");
		execve(argv[0], argv, list_to_array(g_globals->env));
	}
	else
	{
		g_globals->current_pid = pid;
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		g_globals->current_pid = 0;
		printf("Status: %d\n", g_globals->status);
	}

	return 0;
}
