/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:58:35 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/21 15:20:49 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/token.h"

t_token	*new_token(char *str, t_tok_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new)
	{
		new->cmd = str;
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

t_tok_type	attribute_tok_type(char chr)
{
	if (chr == ';')
		return (tok_end_of_cmd);
	else if (chr == '|')
		return (tok_pipe);
	else if (chr == '>')
		return (tok_redir_r);
	else if (chr == '<')
		return (tok_redir_l);
	else
		return (tok_word);
}

t_token	*get_next_token(char *line)
{
	t_tok_type	role;
	char		*cmd;

	skip_spaces(&line);
	role = attribute_tok_type(*line);
	cmd = cut_token_string(line);
	if (cmd)
		return (new_token(cmd, role));
	else
		return (NULL);
}
