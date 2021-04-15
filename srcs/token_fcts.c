/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 09:36:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/15 14:16:33 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

char	*cut_token_string(char *line)
{
	char	*trimmed_str;
	char	*ptr;
	size_t	i;

	ptr = line;
	skip_spaces(&ptr);
	if (is_escape_character(*ptr))
		trimmed_str = get_escaped_string(line);
	else if (is_token_character(*ptr))
		trimmed_str = ft_strndup(ptr, 1);
	else
	{
		i = 0;
		while (ptr[i] && !is_token_character(ptr[i]))
			i++;
		trimmed_str = ft_strndup(ptr, i);
	}
	return (trimmed_str);
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
	if ((chr == ';') || (chr == '|') || (chr == '<')
		|| (chr == '>'))
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
	}
	result = ft_strndup(str, index);
	return (result);
}
