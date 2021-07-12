/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:13:21 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/06 17:43:13 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	heredoc_routine(int fd, char *heredoc_end)
{
	load_heredoc(fd, heredoc_end);
	fd = open("/tmp/heredoc", O_RDONLY);
	if (fd == -1)
		ft_exit_with_error_msg(strerror(errno));
	if (unlink("/tmp/heredoc"))
		ft_exit_with_error_msg(strerror(errno));
	return (fd);
}

void	load_heredoc(int fd, char *heredoc_end)
{
	char	*buffer;
	char	*expanded;
	bool	end;

	end = true;
	while (end)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			display_error("here-document delimited by end-of-file, wanted",
				heredoc_end);
			break ;
		}
		else if (!ft_strncmp(buffer, heredoc_end, ft_strlen(heredoc_end) + 1))
			end = false;
		expanded = expand_text(buffer);
		if (end)
			ft_putendl_fd(expanded, fd);
		free(buffer);
		free(expanded);
	}
	close(fd);
}
