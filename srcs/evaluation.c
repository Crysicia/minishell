/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:21:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/11 12:00:22 by pcharton         ###   ########.fr       */
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
		if (get_flag(&token->flag, _EXPANSION))
		{
			expand_token(token);
			parse_expanded_variable(tmp);
		}
		token = tmp->content;
		remove_quoting(token->cmd);
		tmp = tmp->next;
	}
	return (0);
}

int	expand_token(t_token *token)
{
	char	*buffer;
	char	*to_eval;

	to_eval = token->cmd;
	buffer = expand_text(to_eval);
	free(token->cmd);
	token->cmd = ft_strdup(buffer);
	if (!token->cmd)
		ft_exit_with_error_msg(strerror(errno));
	free(buffer);
	buffer = NULL;
	return (1);
}
