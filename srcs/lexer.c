/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/05 15:04:56 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdbool.h>

void	get_command(void)
{
	char	*line;
	int		ret;

	ret = get_next_line(0, &line);
	if (ret == -1 || line == NULL)
	{
		puts("gnl error");
		exit(-1);
	}
	else if (ret == 0)
		exit(0);
	lexer(line);
}

int	lexer(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	if (line == NULL)
	{
		printf("lexer error");
		return (-1);
	}
	while (*line)
	{
		tmp = get_word(&line);
		printf("%d = |%s|\n", i++, tmp);
		skip_spaces(&line);
	}
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
