/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 07:41:15 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/19 15:29:40 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

	if ((!command) || ((!command->words) && (!command->redirections))
		|| (((t_token *)command->words)->role == operator))
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
