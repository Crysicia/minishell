/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/07 18:18:06 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdbool.h>

void	get_command(char *envp[])
{
	char	*swap;
	char	*tmp;
	char	*line;
	int		ret;

	ret = get_next_line(0, &line);
	if (ret == -1 || line == NULL)
	{
		puts("gnl error");
		exit(-1);
	}
	else if (ret == 0)
	{
		if (ft_strlen(line) == 0)
			exit(0);
		while (ret == 0)
		{
			ret = get_next_line(0, &tmp);
			swap = gnl_join(line, tmp);
			free(line);
			free(tmp);
			line = swap;
		}
	}
	lexer(line, envp);
}

int	lexer(char *line, char *envp[])
{
	t_command	command;

	command.executable = NULL;
	command.args = NULL;
	command.envp = envp;
	if (line == NULL)
	{
		printf("lexer error");
		return (-1);
	}
	command.args = ft_split(line, ' ');
	execute_command(&command);
	return (0);
}

void	skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		*line += 1;
}

char	*get_word(char **line)
{
	int		i;
	int		word_len;
	char	*word;

	i = 0;
	while (*(*line + i) && (*(*line + i) != ' '))
		i++;
	word_len = i;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	else
	{
		word[i] = 0;
		while (i--)
			*(word + i) = *(*line + i);
		*line += word_len;
		return (word);
	}
}
