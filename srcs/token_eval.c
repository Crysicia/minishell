/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_eval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:21:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/24 14:21:54 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include <string.h>

bool	is_valid_token(t_token tok)
{
	if (tok.cmd && ((!strcmp(";", tok.cmd) && (tok.role == tok_end_of_cmd))
			|| ((tok.role == tok_pipe) && !strcmp("|", tok.cmd))
			|| ((tok.role == tok_redir_l) && !strcmp("<", tok.cmd))
			|| ((tok.role == tok_redir_r) && !strcmp(">", tok.cmd))
			|| ((tok.role == tok_append_r) && !strcmp(">>", tok.cmd))))
		return (true);
	else
		return (false);
}

int	execute_routine(t_tok_type token, t_list *list)
{
	(void)list;
	if (token == tok_end_of_cmd)
		return (0);
	else if (token == tok_pipe)
		return (0);
	else if (token == tok_redir_l)
		return (0);
	else if (token == tok_append_r)
		return (0);
	else if (token == tok_redir_l)
		return (0);
	else
		return (0);
}

/*
int	pipe_routine(t_list *list);
int	redir_l_routine(t_list *list);
*/

int	evaluate_token(t_list *list)
{
	t_token		*tok;
	t_tok_type	type;

	tok = list->content;
	if (is_valid_token(*tok))
	{
		type = tok->role;
		return (execute_routine(type, list));
	}
	else
		syntax_error();
	return (-1);
}
