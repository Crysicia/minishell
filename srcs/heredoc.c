/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:13:21 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/05 16:09:32 by pcharton         ###   ########.fr       */
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
	char	output[1024];
	bool	end;

	end = true;
	while (end)
	{
		ft_bzero(output, 1024);		
		buffer = readline("> ");
		if (!buffer)
		{
			display_error("here-document delimited by end-of-file, wanted",
				heredoc_end);
			break ;
		}
		else if (!ft_strncmp(buffer, heredoc_end, ft_strlen(heredoc_end) + 1))
			end = false;
		expand_text(output, &buffer[0]);
		if (end)
			ft_putendl_fd(output, fd);
		free(buffer);
	}
	close(fd);
}
