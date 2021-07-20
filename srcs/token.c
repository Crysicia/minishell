/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:58:35 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/19 12:25:40 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "header.h"

t_token	*new_token(char *str, t_tok_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new)
	{
		new->cmd = str;
		new->flag = 0;
		new->role = type;
	}
	return (new);
}

void	free_token(void *token)
{
	free(((t_token *)token)->cmd);
	free(token);
	token = NULL;
}

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
