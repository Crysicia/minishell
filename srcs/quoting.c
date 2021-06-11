/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 19:35:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/06/11 20:28:26 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	remove_mixed_quotes(t_token *token)
{
	char	*buffer;
	char	*to_eval;

	buffer = ft_calloc(4096, 1);
	if (!buffer)
		ft_exit_with_error_msg(strerror(errno));
	to_eval = token->cmd;
	expand_text(buffer, to_eval);
	free(token->cmd);
	token->cmd = ft_strdup(buffer);
	if (!token->cmd)
		ft_exit_with_error_msg(strerror(errno));
	free(buffer);
}

void	expand_text(char *buffer, char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			expand_env_variable(&str, &buffer);
			str++;
		}
		else if (*str == '\'')
			copy_simple_quoted_text(&str, &buffer);
		else if (*str == '"')
			copy_double_quoted_text(&str, &buffer);
		else
			*buffer++ = *str++;
	}
}

void	copy_simple_quoted_text(char **str, char **buffer)
{
	*str += 1;
	while (**str && (**str != '\''))
	{
		**buffer = **str;
		*buffer += 1;
		*str += 1;
	}
	*str += 1;
}

void	copy_double_quoted_text(char **str, char **buffer)
{
	*str += 1;
	while (**str && (**str != '"'))
	{
		if (**str == '$')
			expand_env_variable(str, buffer);
		else
		{
			**buffer = **str;
			*buffer += 1;
			*str += 1;
		}
	}
	*str += 1;
}
