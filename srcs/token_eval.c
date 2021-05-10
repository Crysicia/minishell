/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_eval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:21:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 14:08:25 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <string.h>

int	execute_routine(t_tok_type token, t_list **list)
{
	char	**tab;

	if (token == word)
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
	type = tok->role;
	return (execute_routine(type, list));
}
