/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_eval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:21:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/27 14:01:16 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <string.h>

bool	is_valid_token(t_token tok)
{
	if (tok.cmd && 
			((!strcmp(";", tok.cmd) && (tok.role == tok_end_of_cmd))
			|| ((tok.role == tok_pipe) && !strcmp("|", tok.cmd))
			|| ((tok.role == tok_redir_l) && !strcmp("<", tok.cmd))
			|| ((tok.role == tok_redir_r) && !strcmp(">", tok.cmd))
			|| ((tok.role == tok_append_r) && !strcmp(">>", tok.cmd))))
		return (true);
	else
		return (false);
}

int	execute_routine(t_tok_type token, t_list **list)
{
	char	**tab;

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
	else if (token == tok_word)
	{
		tab = command_format(list);
		execute_command(tab);
		if (g_globals->status != 0)
			printf("Status: %d\n", g_globals->status);
		return (0);
	}
	else
	{
		syntax_error();
		return (-1);
	}
}

/*
int	pipe_routine(t_list *list);
int	redir_l_routine(t_list *list);
*/

int	evaluate_token(t_list **list)
{
	t_token		*tok;
	t_tok_type	type;

	tok = (*list)->content;
	if (((tok->role != tok_word) && is_valid_token(*tok))
		|| (tok->role == tok_word))
	{
		type = tok->role;
		return (execute_routine(type, list));
	}
	else
	{
		syntax_error();
		return (-1);
	}
}
