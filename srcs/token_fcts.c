/* ************************************************************************** */
/*                                                                            */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 09:36:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/30 09:45:02 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

int		get_word_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_operator(line + i)
	   && !is_space(line[i]))
	{
		if (line[i] == '\\')
			i++;
		//protect \\0 case
		i++;
	}
	return (i);
}

char	*cut_token_string(char *line)
{
	char	*trimmed_str;

	if (is_escape_character(*line))
		trimmed_str = get_escaped_string(line);
	else if (is_operator(line) && (!ft_strncmp(">>", line, 2)))
		trimmed_str = ft_strndup(line, 2);
	else if (is_operator(line) && ft_strchr(";|<>", *line))
		trimmed_str = ft_strndup(line, 1);
	else
		trimmed_str = ft_strndup(line, get_word_size(line));
	if (!trimmed_str)
		ft_malloc_error();
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

bool	is_operator(char *str)
{
	if ((*str == ';') || (*str == '|') || (*str == '<') || (*str == '>')
		|| !ft_strncmp(str, ">>", 2))
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
