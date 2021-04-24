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
/*
int	evaluate_token(t_token token)
{
	if (token)
//((chr == ';') || (chr == '|') || (chr == '<') || (chr == '>'))
		return (-1);
	else
		return (0);
}*/