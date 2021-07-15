/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:42:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/15 15:37:18 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	check_command_syntax(t_list *list)
{
	size_t	index;
	char	*tmp;

	index = count_command_words(list);
	if (!index)
	{
		if (!ft_strncmp(((t_token *)list->content)->cmd, "|", 1))
			tmp = "pipe";
		else if (!ft_strncmp(((t_token *)list->content)->cmd, ";", 1))
			tmp = "semi-colon";
		else
			tmp = "newline";
		printf("-Minishell: syntax error near unexpected `%s` token\n",
			tmp);
		return (false);
	}
	else
		return (true);
}

bool	check_redirections(t_list *list)
{
	t_list			*node;
	t_redirection	*redir;
	t_token			*tok;

	node = list;
	while (node)
	{
		redir = node->content;
		tok = redir->file;
		if (tok->role != word)
		{
			display_error("unexpected syntax error near `newline'", NULL);
			return (true);
		}
		node = node->next;
	}
	return (false);
}

bool	check_first_node_cmd(t_simple_command *cmd)
{
	t_token	*tok;

	if (cmd->words)
	{
		tok = cmd->words->content;
		if (tok && tok->role == operator)
		{
			parser_error(tok);
			return (true);
		}
	}
	if (cmd->redirections)
		return (check_redirections(cmd->redirections));
	return (false);
}

bool	check_pipeline(t_pipeline *pipeline)
{
	t_list	*node;

	node = pipeline->commands;
	while (node)
	{
		if (!node || check_first_node_cmd(node->content))
			return (true);
		node = node->next;
	}
	return (false);
}

bool	check_syntax_error(t_list *list)
{
	t_list	*tmp;
	t_block	*block;

	tmp = list;
	while (tmp)
	{
		block = tmp->content;
		if ((block->id == simple_command)
			&& (check_first_node_cmd(block->kind.cmd)))
			return (true);
		else if (block->id == pipeline && check_pipeline(block->kind.pipe))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
