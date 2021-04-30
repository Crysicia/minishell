/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 09:36:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/29 11:31:59 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

/*
**	protect the case \\0
** Throw and error and stop execution, the quote removal fct will segv
** for that case!
*/

int	get_word_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_operator(line + i)
		&& !is_space(line[i]))
	{
		if (line[i] == '\\')
			i++;
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
		while (ft_isalnum(str[index]))
			index++;
	}
	result = ft_strndup(str, index);
	

	
	return (result);
}
