/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:35:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/15 15:29:51 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	handle_redirections(t_list *command)
{
	t_redirection	*redirection;
	t_list			*node;

	node = command;
	while (node)
	{
		redirection = node->content;
		word_flagger(redirection->file);
		if (redirection->file->role)
		{
			if (expand_redirection(redirection))
				return (1);
		}
		redirection->fd = create_file(redirection->file->cmd,
				redirection->operator->cmd);
		if (redirection->fd == -1)
			return (1);
		node = node->next;
	}
	return (0);
}

int	expand_redirection(t_redirection *redirection)
{
	char			*expanded_str;

	expanded_str = expand_text(redirection->file->cmd);
	if (!expanded_str)
	{
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
		return (-1);
	}
	else if (!*expanded_str)
	{
		display_error(redirection->file->cmd, "Ambiguous redirect");
		redirection->fd = -1;
		return (1);
	}
	else
	{
		free(redirection->file->cmd);
		redirection->file->cmd = expanded_str;
		return (0);
	}
}

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

int	apply_all_redirections(t_list *command)
{
	t_redirection	*redirection;
	t_list			*node;

	node = command;
	while (node)
	{
		redirection = node->content;
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

void	apply_redirection(int fd, char *redirection_type)
{
	int	tmp;

	if (fd > -1)
	{
		if (!ft_strcmp(redirection_type, "<")
			|| !ft_strcmp(redirection_type, "<<"))
		{
			tmp = dup2(fd, STDIN_FILENO);
			if (tmp < 0)
				display_error(strerror(errno), NULL);
		}
		else
		{
			tmp = dup2(fd, STDOUT_FILENO);
			if (tmp < 0)
				display_error(strerror(errno), NULL);
		}
		close(fd);
	}
}
