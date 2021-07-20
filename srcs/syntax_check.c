/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:42:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/20 12:22:19 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
			update_last_seen_token(tok);
			parser_error();
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
		if (tok && tok->role == operator && !cmd->redirections)
		{
			parser_error();
			return (true);
		}
	}
	if (cmd->redirections)
		return (check_redirections(cmd->redirections));
	if (!cmd->words && !cmd->redirections)
	{
		parser_error();
		return (true);
	}
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
		print_simple_command_node(node->content);
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
