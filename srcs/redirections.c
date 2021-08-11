/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:35:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/08/11 17:34:34 by pcharton         ###   ########.fr       */
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
		if (redirection->file->role
			&& get_flag(&redirection->file->flag, _EXPANSION)
			&& ft_strcmp("<<", redirection->operator->cmd))
		{
			if (expand_redirection(redirection))
				return (close_all_fds(command));
		}
		remove_quoting(redirection->file->cmd);
		if (ft_strcmp("<<", redirection->operator->cmd))
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
	char	*expanded_str;

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

void	create_pipeline_files(t_pipeline *pipeline)
{
	t_list				*node;
	t_simple_command	*cmd;

	node = pipeline->commands;
	while (node)
	{
		cmd = node->content;
		handle_redirections(cmd->redirections);
		node = node->next;
	}
}
