/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:31:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 14:56:30 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/token.h"

t_list	*parse_to_list(char *line)
{
	char	*ptr;
	t_token	*token;
	t_list	*tokens;
	t_list	*node;

	ptr = line;
	tokens = NULL;
	while (*ptr)
	{
		token = get_next_token(ptr);
		node = ft_lstnew(token);
		if (!token || !node)
		{
			if (token)
				free_token(token);
			ft_lstclear(&tokens, free_token);
			return (NULL);
		}
		ft_lstadd_back(&tokens, node);
		ptr = ft_strnstr(ptr, token->cmd, ft_strlen(ptr));
		ptr += ft_strlen(token->cmd);
	}
	return (tokens);
}

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

/*
void	parser_loop(char *line)
{

}
*/

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
			else if (!ft_strncmp("|", token->cmd, 2))
			{;}
			else if (!ft_strncmp(";", token->cmd, 2))
			{;}
		}
		else
			ft_lstadd_back(&(save->words), new_word);
	}
	return (save);
}

void	parse_redirection(char **line, t_simple_command *command, t_token *token)
{
	t_list			*new_node;
	t_redirection	*new_redir;
	t_token			*file;

	file = get_next_token_rework(line);
	if (file->role == word)
	{
		new_redir = new_redirection();
		new_redir->operator = token;
		new_redir->file = file;
		new_node = ft_lstnew(new_redir);
		ft_lstadd_back(&(command->redirections), new_node);
	}
	else
		display_error("syntax error near unexpected token", NULL);
}

/*

t_pipeline	*parse_pipeline(void)
{

}
*/

size_t	count_command_words(t_list *list)
{
	size_t	index;
	t_list	*tmp;
	t_token	*tok;

	index = 0;
	tmp = list;
	tok = tmp->content;
	while (tmp && (tok->role == word))
	{
		index++;
		tmp = tmp->next;
		if (tmp)
			tok = tmp->content;
	}
	return (index);
}

char	**command_format(t_list **list)
{
	t_list	*tmp;
	t_token	*tok;
	size_t	index;
	size_t	count;
	char	**tab;

	count = 0;
	index = count_command_words(*list);
	tab = malloc(sizeof(char **) * (index + 1));
	if (!tab)
		ft_malloc_error();
	while (count < index)
	{
		tmp = *list;
		tok = tmp->content;
		tab[count] = ft_strdup(tok->cmd);
		count++;
		*list = (*list)->next;
	}
	if (*list && (((t_token *)(*list)->content)->role == operator)
			&& ft_strncmp(((t_token *)(*list)->content)->cmd, ";", 2))
		*list = (*list)->next;
	tab[count] = NULL;
	return (tab);
}
