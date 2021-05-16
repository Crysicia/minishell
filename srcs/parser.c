/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:54:25 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 17:22:47 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/token.h"

t_token	*get_next_token_rework(char **line)
{
	t_tok_type	role;
	char		*cmd;

	skip_spaces(line);
	role = get_token_role(*line);
	cmd = cut_token_string(*line);
	if (cmd)
	{
		*line = ft_strnstr(*line, cmd, ft_strlen(cmd));
		*line += ft_strlen(cmd);
		return (new_token(cmd, role));
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
		node = parse_simple_command(&ptr);
		if (node->id == pipeline)
		{
			parse_pipeline_command(&ptr, node);
		}
		ft_lstadd_back(&parsed_list, ft_lstnew(node));
	}
	return (parsed_list);
}

t_block	*parse_simple_command(char **line)
{
	t_simple_command	*save;
	t_token				*token;
	t_list				*new_word;
	t_block				*node;

	save = new_simple_command();
	while (**line)
	{
		token = get_next_token_rework(line);
		new_word = ft_lstnew_safe(token, free_token);
		if (token->role == redirection)
			parse_redirection(line, save, token);
		else
			ft_lstadd_back(&(save->words), new_word);
		if (token->role == operator)
			break ;
	}
	node = new_block();
	node->id = attribute_command_type(save->words);
	node->kind.cmd = save;
	return (node);
}
/* 			else if (!ft_strncmp("|", token->cmd, 2)) {;}			*/

void	parse_redirection(char **line, t_simple_command *command, t_token *tok)
{
	t_list			*new_node;
	t_redirection	*new_redir;
	t_token			*file;

	puts("hello");
	file = get_next_token_rework(line);
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
	puts("helloe");
}

void	parse_pipeline_command(char **line, t_block *block)
{
	t_pipeline			*new;
	t_simple_command	*command;
	t_block				*tmp;
	t_list				*node;

	new = new_pipeline(block->kind.cmd);
	command = (block->kind.cmd);
	while (check_if_pipeline(command))
	{
		tmp = parse_simple_command(line);
		command = tmp->kind.cmd;
		node = ft_lstnew(tmp);
		ft_lstadd_back(&new->commands, node);
		new->pipe_count += 1;
	}
	block->kind.pipe = new;
}
