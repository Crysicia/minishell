/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 09:36:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/16 11:53:23 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*get_next_token(char **line)
{
	char		*cmd;

	skip_spaces(line);
	cmd = cut_token_string(*line);
	if (cmd)
	{
		*line = ft_strnstr(*line, cmd, ft_strlen(cmd));
		*line += ft_strlen(cmd);
		return (new_token(cmd, get_token_role(cmd)));
	}
	else
		return (NULL);
}

char	*cut_token_string(char *line)
{
	char	*trimmed_str;

	if (is_redirection(line)
		&& (!ft_strncmp(">>", line, 2) || !ft_strncmp("<<", line, 2)))
		trimmed_str = ft_strndup(line, 2);
	else if ((is_operator(line) && ft_strchr("|", *line))
		|| (is_redirection(line) && ft_strchr("><", *line)))
		trimmed_str = ft_strndup(line, 1);
	else
		trimmed_str = ft_strndup(line, get_word_size(line));
	return (trimmed_str);
}

int	get_word_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_operator(&line[i]) && !is_redirection(&line[i])
		&& !is_space(line[i]))
	{
		if (ft_strchr("'\"", line[i]) && is_quote_closed(line[i], &line[i]))
			i += add_quote_len(line[i], &line[i]);
		i++;
	}
	return (i);
}

bool	is_quote_closed(char quote, char *str)
{
	str++;
	while (*str)
	{
		if (*str == quote)
			return (true);
		str++;
	}
	return (false);
}

int	add_quote_len(char quote, char *str)
{
	int	len;

	len = 1;
	while (str[len] && str[len] != quote)
		len++;
	return (len);
}
