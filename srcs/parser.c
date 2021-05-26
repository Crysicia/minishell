/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:54:25 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:37:23 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "token.h"

t_token	*get_next_token(char **line)
{
	char		*cmd;

	skip_spaces(line);
	cmd = cut_token_string(*line);
	if (cmd)
	{
		*line = ft_strnstr(*line, cmd, ft_strlen(cmd));
		*line += ft_strlen(cmd);
		return (new_token(cmd, get_token_role(cmd)));
	}
	else
		return (NULL);
}

t_list	*parser_loop(char *line)
{
	char	*ptr;
	t_list	*parsed_list;
	t_block	*node;

	ptr = line;
	parsed_list = NULL;
	while (*ptr)
	{
		node = new_block();
		parse_simple_command(node, &ptr);
		if (node->id == pipeline)
			parse_pipeline_command(node, &ptr);
		ft_lstadd_back(&parsed_list, ft_lstnew(node));
	}
	return (parsed_list);
}

int	parse_simple_command(t_block *dst, char **line)
{
	t_simple_command	*new;
	t_token				*token;

	new = new_simple_command();
	if (!new)
		return (ERR_MALLOC_FAILED);
	while (**line)
	{
		token = get_next_token(line);
		if (!token)
			return (ERR_MALLOC_FAILED);
		else if (token->role == redirection)
			parse_redirection(line, new, token);
		else
			ft_lstadd_back(&(new->words), ft_lstnew_safe(token, free_token));
		if (token->role == operator)
			break ;
	}
	dst->id = attribute_command_type(new);
	dst->kind.cmd = new;
	return (0);
}
/* 			else if (!ft_strncmp("|", token->cmd, 2)) {;}			*/

void	parse_redirection(char **line, t_simple_command *command, t_token *tok)
{
	t_list			*new_node;
	t_redirection	*new_redir;
	t_token			*file;

	file = get_next_token(line);
	if (file->role == word)
	{
		new_redir = new_redirection();
		new_redir->operator = tok;
		new_redir->file = file;
		new_node = ft_lstnew(new_redir);
		ft_lstadd_back(&(command->redirections), new_node);
	}
	else
		display_error("syntax error near unexpected token", NULL);
}

int	parse_pipeline_command(t_block *block, char **line)
{
	t_pipeline			*new;
	t_simple_command	*command;
	t_block				tmp;
	t_list				*node;

	new = new_pipeline(block->kind.cmd);
	if (!new)
		return (ERR_MALLOC_FAILED);
	command = block->kind.cmd;
	while (check_if_pipeline(command))
	{
		parse_simple_command(&tmp, line);
		command = tmp.kind.cmd;
		node = ft_lstnew(command);
		if (!node)
			return (ERR_MALLOC_FAILED);
		ft_lstadd_back(&new->commands, node);
		new->pipe_count += 1;
	}
	block->kind.pipe = new;
	return (0);
}
