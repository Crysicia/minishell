/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:35:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/24 12:32:24 by lpassera         ###   ########.fr       */
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
	fd = open(path, open_flags, 0644);
	if (fd == -1)
		display_error(path, strerror(errno));
	return (fd);
}

void	apply_redirection(int fd, char *redirection_type)
{
	if (!ft_strcmp(redirection_type, "<"))
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	handle_redirections(t_list *command)
{
	t_redirection	*redirection;
	t_list			*node;

	if (flag_redirection(command))
		return (1);
	node = command;
	while (node)
	{
		redirection = node->content;
		redirection->fd = create_file(redirection->file->cmd, redirection->operator->cmd);
		if (redirection->fd == -1)
			return (1);
		node = node->next;
	}
	node = command;
	while (node)
	{
		redirection = node->content;
		apply_redirection(redirection->fd, redirection->operator->cmd);
		node = node->next;
	}
	return (0);
}

bool	save_in_and_out(int (*saved)[])
{
	ft_bzero(*saved, 2 * sizeof(int));
	(*saved)[0] = dup(STDOUT_FILENO);
	if ((*saved)[0] == -1)
		return (false);
	(*saved)[1] = dup(STDIN_FILENO);
	if ((*saved)[1] == -1)
	{
		close((*saved)[0]);
		return (false);
	}
	return (true);
}

bool	restore_in_and_out(int (*saved)[])
{
	bool	ret;

	ret = true;
	if (dup2((*saved)[0], STDOUT_FILENO) == -1
			|| dup2((*saved)[1], STDIN_FILENO) == -1)
		ret = false;
	close((*saved)[0]);
	close((*saved)[1]);
	return (ret);
}
