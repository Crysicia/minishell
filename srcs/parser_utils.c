/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 07:41:15 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/11 12:01:17 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token	*get_last_node_toktype(t_list	*list)
{
	t_list		*tmp;
	t_token		*tok;

	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tok = tmp->content;
	return (tok);
}

t_command_type	attribute_command_type(t_simple_command *command)
{
	t_token	*token;

	if ((!command) || ((!command->words) && (!command->redirections)))
		return (error);
	else if ((!command->words) && (command->redirections))
		return (only_redirections);
	else
	{
		token = get_last_node_toktype(command->words);
		if ((token->role == operator) && (!ft_strncmp("|", token->cmd, 2)))
			return (pipeline);
		else
			return (simple_command);
	}
}

/*
**
**  Get a !command! node to expand
**  Parse it in one or more nodes
**  Insert the node between the others
**
*/

int	parse_expanded_variable(t_list *node)
{
	t_list	*end;
	t_list	*new;
	t_token	*to_replace;
	char	*expanded_str_to_parse;
	t_token	*token;

	token = node->content;
	to_replace = node->content;
	expanded_str_to_parse = token->cmd;
	end = node->next;
	token = get_next_token(&expanded_str_to_parse);
	new = get_other_arguments(expanded_str_to_parse, end);
	free_token(to_replace);
	node->content = token;
	node->next = new;
	return (0);
}

t_list	*get_other_arguments(char *str, t_list *end)
{
	t_list	*new;
	t_token	*token;

	new = NULL;
	while (*str)
	{
		token = get_next_token(&str);
		token->role = word;
		ft_lstadd_back(&new, ft_lstnew_safe(token, free_token));
	}
	ft_lstadd_back(&new, end);
	return (new);
}
