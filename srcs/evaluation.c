/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:21:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/12 13:05:16 by pcharton         ###   ########.fr       */
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
		else if (ptr->id == pipeline)
			ret = flag_pipeline(ptr->kind.pipe);
		if (!ret)
			tmp = tmp->next;
		else
			return (-1);
	}
	return (0);
}

int	flag_pipeline(t_pipeline *list)
{
	t_list				*node;
	t_simple_command	*to_flag;

	node = list->commands;
	while (node)
	{
		to_flag = node->content;
		if (flag_simple_command(to_flag))
			ft_exit_with_error_msg("error while flagging pipeline");
		node = node->next;
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
		if (token->flag)
			remove_mixed_quotes(token);
		tmp = tmp->next;
	}
	return (0);
}

int	flag_redirection(t_list *list)
{
	t_redirection	*redir;
	t_list			*node;
	char			*expanded_str;

	node = list;
	while (node)
	{
		redir = node->content;
		word_flagger(redir->file);
		expanded_str = expand_text(redir->file->cmd);
		if (!*expanded_str)
		{
			display_error(redir->file->cmd, "Ambiguous redirect");
			return (1);
		}
		else
		{
			free(redir->file->cmd);
			redir->file->cmd = ft_strdup(expanded_str);
		}
		node = node->next;
	}
	return (0);
}
