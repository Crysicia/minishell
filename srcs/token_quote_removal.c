/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_removal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:57:20 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:39:57 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

void	quotes_removal(t_token *tok)
{
	size_t	len;
	char	*str;
	char	buffer[4096];

	str = tok->cmd;
	len = ft_strlen(str);
	ft_bzero(buffer, 4096);
	if (len > 4096)
	{
		ft_putstr_fd("error command is over 4096 character\n", 1);
		exit(-1);
	}
	remove_simple_and_double_quotes(buffer, str);
	if (ft_strlen(&buffer[0]) < ft_strlen(str))
	{
		free(tok->cmd);
		tok->cmd = ft_strdup(&buffer[0]);
		if (!tok->cmd)
			ft_malloc_error();
	}
}

int	copy_quoted_string(char quote, char *str, char *buffer)
{
	size_t	index;

	index = 1;
	while (str[index] != quote)
	{
		buffer[index - 1] = str[index];
		index++;
	}
	return (index);
}

void	remove_simple_and_double_quotes(char *buffer, char *str)
{
	size_t	index;
	size_t	tmp;
	char	*writer;

	index = 0;
	writer = buffer;
	while (str[index])
	{
		if (str[index] == '\\')
		{
			*writer++ = str[index++];
			*writer++ = str[index++];
		}
		else if (str[index] == '\'' || str[index] == '"')
		{
			tmp = copy_quoted_string(str[index], str + index, writer);
			index += tmp + 1;
			writer += tmp - 1;
		}
		else
			*writer++ = str[index++];
	}
}
