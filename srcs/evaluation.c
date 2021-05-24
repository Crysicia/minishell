/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:54:52 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/24 17:46:56 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	evaluation_pass(t_list *list)
{
	t_list	*tmp;
	t_block	*ptr;

	tmp = list;
	while (tmp)
	{
		ptr = list->content;
		if (ptr->id == simple_command)
			flag_simple_command(ptr->kind.cmd);
		tmp = tmp->next;
	}
	return (0);
}

int	flag_simple_command(t_simple_command *list)
{
	t_list			*tmp;
	t_redirection	*redir;

	tmp = list->words;
	while (tmp)
	{
		word_flagger(tmp->content);
		apply_expansion_and_remove_quotes(tmp->content);
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
	if (token->role == word)
	{
		token->flag = check_quoting(token->cmd);
		if (token->flag == QUOTING_ERROR)
		{
			ft_putendl_fd("Minishell: error: quotes were not closed properly",
				2);
		}
	}
}

void	apply_expansion_and_remove_quotes(t_token *token)
{
	if (!(token->flag)
		|| (token->flag == DOUBLE_QUOTES))
		dollar_expansion(token);
	quotes_removal(token);
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
