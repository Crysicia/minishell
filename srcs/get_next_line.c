/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:20:17 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/06 14:39:05 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_read(int fd, char **line, char *buf)
{
	int		output;
	char	*temp;

	output = read(fd, buf, BUFFER_SIZE);
	while (output > 0)
	{
		temp = *line;
		if (output > 0)
			buf[output] = '\0';
		*line = gnl_join(temp, buf);
		free(temp);
		if (!*line)
			return (-1);
		output = gnl_strchr(&buf[0], '\n');
		if (output > 0)
		{
			gnl_strcpy_and_fill(&buf[0], &buf[output]);
			return (1);
		}
		output = read(fd, buf, BUFFER_SIZE);
	}
	output = 0;
	while (buf[output])
		buf[output++] = '\0';
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			output;

	if (!line || read(fd, *line, 0) || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	*line = gnl_strdup(buffer, 1);
	if (*line == NULL)
		return (-1);
	output = gnl_strchr(&buffer[0], '\n');
	if (output > 0)
	{
		gnl_strcpy_and_fill(&buffer[0], &buffer[output]);
		return (1);
	}
	else
		return (gnl_read(fd, line, buffer));
}
