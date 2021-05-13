/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:35:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/14 01:35:02 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int create_file(char *path, char *redirection_type)
{
	int fd;
	int open_flags;

	if (ft_strcmp(redirection_type, "<"))
		open_flags = O_CREATE;
	if (!ft_strcmp(redirection_type, ">>"))
		open_flags |= O_APPEND;
	fd = open(path. open_flags);
	return (fd);
}

int apply_redirections(char *path, char *redirection_type)
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
	return 0;
}
