/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 09:36:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/21 15:06:10 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

char	*cut_token_string(char *line)
{
	char	*trimmed_str;
	size_t	i;

	if (is_escape_character(*line))
		trimmed_str = get_escaped_string(line);
	else if (is_token_character(*line))
		trimmed_str = ft_strndup(line, 1);
	else
	{
		i = 0;
		while (line[i] && !is_token_character(line[i])
			   && !is_space(line[i]))
		{
			if (line[i] == '\\')
				i++;
			i++;
		}
		trimmed_str = ft_strndup(line, i);
	}
	return (trimmed_str);
}

bool	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

bool	is_escape_character(char chr)
{
	if (chr == '"' || chr == '\'' || chr == '\\')
		return (1);
	else
		return (0);
}

bool	is_token_character(char chr)
{
	if ((chr == ';') || (chr == '|') || (chr == '<') || (chr == '>'))
		return (1);
	else
		return (0);
}

char	*get_escaped_string(char *str)
{
	char	*result;
	char	quote;
	size_t	index;

	index = 0;
	while (str[index] && is_escape_character(str[index]))
	{
		quote = str[index++];
		while (str[index] && (str[index] != quote))
		{
			if (str[index] == '\\')
				index++;
			index++;
		}
		if (str[index] && str[index] == quote)
			index++;
	}
	result = ft_strndup(str, index);
	return (result);
}
