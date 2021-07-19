/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:08:51 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/19 12:09:21 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	if (!ft_strcmp(redirection_type, "<<"))
		fd = open("/tmp/heredoc", open_flags, 0644);
	else
		fd = open(path, open_flags, 0644);
	if (fd == -1)
		display_error(path, strerror(errno));
	if (!ft_strcmp(redirection_type, "<<"))
		fd = heredoc_routine(fd, path);
	return (fd);
}

int	close_all_fds(t_list *command)
{
	t_redirection	*redirection;
	t_list			*node;

	node = command;
	while (node)
	{
		redirection = node->content;
		close(redirection->fd);
		node = node->next;
	}
	return (1);
}
