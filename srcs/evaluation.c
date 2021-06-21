/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:21:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/06/11 19:41:10 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	evaluation_pass(t_list *list)
{
	t_list	*tmp;
	t_block	*ptr;
	int		ret;

	ret = 0;
	tmp = list;
	while (tmp)
	{
		ptr = list->content;
		if (ptr->id == simple_command)
			ret = flag_simple_command(ptr->kind.cmd);
		if (!ret)
			tmp = tmp->next;
		else
			return (-1);
	}
	return (0);
}

int	flag_simple_command(t_simple_command *list)
{
	t_token			*token;
	t_list			*tmp;

	tmp = list->words;
	while (tmp)
	{
		token = tmp->content;
		word_flagger(token);
		if (token->flag != QUOTING_ERROR)
			remove_mixed_quotes(token);
		else
			return (-1);
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

/*
int	flag_pipeline(t_pipeline *list)
{
	return (0);
}
*/

int	flag_redirection(t_list *list)
{
	t_redirection	*redir;
	t_list			*node;
	char			buffer[1024];

	node = list;
	while (node)
	{
		ft_bzero(buffer, 1024);
		redir = node->content;
		word_flagger(redir->file);
		expand_text(buffer, redir->file->cmd);
		if (!*buffer)
		{
			display_error(redir->file->cmd, "Ambiguous redirect");
			return (1);
		}
		else
		{
			free(redir->file->cmd);
			redir->file->cmd = ft_strdup(buffer);
		}
		node = node->next;
	}
	return (0);
}
