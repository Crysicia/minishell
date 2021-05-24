/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:54:52 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/24 08:54:52 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	flag_simple_command(t_simple_command *list)
{
	t_list			*tmp;
	t_redirection	*redir;

	tmp = list->words;
	while (tmp)
	{
		word_flagger(tmp->content);
		tmp = tmp->next;
	}
	tmp = list->redirections;
	while (tmp)
	{
		redir = tmp->content;
		word_flagger(redir->file);
		tmp = tmp->next;
	}
	return (0);
}

void	word_flagger(t_token *token)
{
	puts("call to word flagger");
	if (token->role == word)
	{
		token->flag = check_quoting(token->cmd);
		if (token->flag == QUOTING_ERROR)
		{
			ft_putendl_fd("Minishell: error: quotes were not closed properly",
				2);
		}
		else
			dollar_expansion(token);
	}
}

/*

int	flag_pipeline(t_pipeline *list)
{
	return (0);
}

int	flag_redirection(t_list *list)
{

	return (0);
}
*/