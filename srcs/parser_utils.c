/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 07:41:15 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 17:06:55 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_command_type	attribute_command_type(t_list *words)
{
	t_list		*tmp;
	t_token		*tok;
	t_tok_type	type;

	tmp = words;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tok = tmp->content;
	type = get_token_role(tok->cmd);
	if ((type == operator) && (!ft_strncmp("|", tok->cmd, 2)))
		return (pipeline);
	else
		return (simple_command);
}
