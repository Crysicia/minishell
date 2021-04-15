/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:58:35 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/15 15:16:07 by pcharton         ###   ########.fr       */
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

t_list	*command_parse(char *line)
{
	char	*ptr;
	t_token	*token;
	t_list	*tokens;
	t_list	*node;

	ptr = line;
	tokens = NULL;
	while (*ptr)
	{
		skip_spaces(&ptr);
		token = get_next_token(ptr);
		node = ft_lstnew(token);
		if (!token || !node)
		{
			if (token)
				free_token(token);
			ft_lstclear(&tokens, free_token);
			return (NULL);
		}
		ft_lstadd_back(&tokens, node);
		ptr = ft_strnstr(ptr, token->cmd, ft_strlen(ptr));
		ptr += ft_strlen(token->cmd);
	}
	return (tokens);
}

t_tok_type	attribute_tok_type(char chr)
{
	if (chr == ';')
		return (tok_end_of_cmd);
	else if (chr == '|')
		return (tok_pipe);
	else if (chr == '>')
		return (tok_redir_l);
	else if (chr == '<')
		return (tok_redir_r);
	else
		return (tok_command);
}

t_token	*get_next_token(char *line)
{
	t_tok_type	role;
	char		*cmd;

	role = attribute_tok_type(*line);
	cmd = cut_token_string(line);
	if (cmd)
		return (new_token(cmd, role));
	else
		return (NULL);
}
