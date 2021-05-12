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
	if (is_operator(*line))
		role = operator;
	else
		role = word;
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
	t_list	*last;

	ptr = line;
	parsed_list = NULL;
	while (*ptr)
	{
		last = ft_lstnew(parse_simple_command(&ptr));
		check_if_pipeline(last->content);
		ft_lstadd_back(&parsed_list, last);
	}
	return (parsed_list);
}

t_simple_command	*parse_simple_command(char **line)
{
	t_simple_command	*save;
	t_token				*token;
	t_list				*new_word;

	save = new_simple_command();
	while (**line)
	{
		token = get_next_token_rework(line);
		new_word = ft_lstnew_safe(token, free_token);
		if (token->role == operator)
		{
			if (is_redirection(token->cmd))
				parse_redirection(line, save, token);
			else if (ft_strchr("|;", *token->cmd))
			{
				ft_lstadd_back(&(save->words), new_word);
				break ;
			}
		}
		else
			ft_lstadd_back(&(save->words), new_word);
	}
	return (save);
}
/* 			else if (!ft_strncmp("|", token->cmd, 2)) {;}			*/

void	parse_redirection(char **line, t_simple_command *command, t_token *tok)
{
	t_list			*new_node;
	t_redirection	*new_redir;
	t_token			*file;

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
}

bool	check_if_pipeline(t_simple_command	*command)
{
	t_list	*node;
	t_token	*token;

	if (command->redirections)
		return (0);
	node = command->words;
	while (node)
	{
		token = node->content;
		if (!ft_strncmp(token->cmd, "|", 2))
			return (1);
		node = node->next;
	}
	return (0);
}
/*
t_pipeline	*parse_pipeline_command(char **line, t_simple_command *first)
{
	t_pipeline			*new;
	t_simple_command	*command;

	new = new_pipeline(first);
	command = first;
	while (check_if_pipeline(command))
	{
		command = parse_simple_command(line);
		ft_lstadd_back(&new->commands, ft_lstnew(command));
	}
	return (new);
}
*/