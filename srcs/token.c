/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:58:35 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 14:39:18 by pcharton         ###   ########.fr       */
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