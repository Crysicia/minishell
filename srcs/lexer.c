/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/06 16:21:56 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdbool.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void	get_command(void)
{
	char	*line;
	int		ret;

	line = calloc(512, 1);
	ret = get_next_line(0, &line);
	if (ret == -1 || line == NULL)
	{
		puts("gnl error");
		exit(-1);
	}
	else if (!ft_strlen(line))
	{
		write(1, "\n", 1);
		exit (0);
	}
	else if (ret == 0)
		gnl_loop_function(line);
	if (is_valid_command(line))
		lexer(line);
	else
		printf("line contains forbidden characters\n");
}

bool	gnl_loop_function(char *line)
{
	int		ret;
	char	*swap;
	char	*tmp;

	ret = 0;
	while (ret == 0)
	{
		ret = get_next_line(0, &tmp);
		swap = gnl_join(line, tmp);
		free(line);
		free(tmp);
		line = swap;
	}
	return (true);
}

int	lexer(char *line)
{
	char	**formatted_line;

	if (line == NULL)
	{
		printf("lexer error : line is NULL at line %d of %s\n",
			__LINE__, __FILE__);
		return (-1);
	}
	printf("valid line is [%s]\n", line);
	formatted_line = evaluate_command(line);
	puts("here is the tab** sent to exec function :");
	while (formatted_line && *formatted_line)
		puts(*(formatted_line++));
	return (0);
}



void	skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		*line += 1;
}
