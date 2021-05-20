/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:35:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/19 14:49:01 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	create_file(char *path, char *redirection_type)
{
	int	fd;
	int	open_flags;

	open_flags = O_RDWR;
	if (ft_strcmp(redirection_type, "<"))
		open_flags |= O_CREAT;
	if (!ft_strcmp(redirection_type, ">>"))
		open_flags |= O_APPEND;
	if (ft_strcmp(redirection_type, ">>") && ft_strcmp(redirection_type, "<"))
		open_flags |= O_TRUNC;
	fd = open(path, open_flags, 0644);
	return (fd);
}

void	apply_redirection(char *path, char *redirection_type)
{
	int	fd;

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

void	handle_redirections(t_list *command)
{
	t_redirection	*redirection;

	while (command)
	{
		redirection = command->content;
		apply_redirection(redirection->file->cmd, redirection->operator->cmd);
		command = command->next;
	}
}
