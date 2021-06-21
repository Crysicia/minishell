/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:13:21 by pcharton          #+#    #+#             */
/*   Updated: 2021/06/21 14:13:21 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	heredoc_routine(int fd, char *heredoc_end)
{
	load_heredoc(fd, heredoc_end);
	fd = open("/tmp/heredoc", O_RDONLY);
	if (fd == -1)
		ft_exit_with_error_msg(strerror(errno));
	return (fd);
}

void	load_heredoc(int fd, char *heredoc_end)
{
	char	buffer[1024];
	char	output[1024];
	bool	end;
	size_t	read_count;

	end = false;
	while (1)
	{
		ft_bzero(buffer, 1024);
		ft_bzero(output, 1024);		
		read_count = read(0, buffer, 512);
		if (!read_count)
			display_error("here-document delimited by end-of-file, wanted",
				heredoc_end);
		else if ((read_count == ft_strlen(heredoc_end) + 1)
			&& (!ft_strncmp(buffer, heredoc_end, ft_strlen(heredoc_end))))
			end = true;
		expand_text(output, buffer);
		if (!end)
			write(fd, output, ft_strlen(output));
		if (!read_count || end)
			break ;
	}
	close (fd);
}
