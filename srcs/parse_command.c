/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:31:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/19 14:40:10 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/token.h"

t_list	*command_parse(char *line)
{
	char	*ptr;
	t_token	*token;
	t_list	*tokens;
	t_list	*node;

	ptr = line;
	tokens = NULL;
	while (*ptr)
	{
		skip_spaces(&ptr);
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

char	**command_format(t_list *list)
{
	t_list	*tmp;
	t_token	*tok;
	size_t	index;
	size_t	count;
	char	**tab;

	tmp = list;
	tok = list->content;
	index = 0;
	count = 0;
	while (tmp && (tok->role == tok_word))
	{
		index++;
		tmp = tmp->next;
		if (tmp)
			tok = tmp->content;
	}
	tab = malloc(sizeof(char **) * (index + 1));
	if (!tab)
		return (NULL);
	else
	{
		tmp = list;
		tok = list->content;
		while (count < index)
		{
			tab[count] = ft_strdup(tok->cmd);
			if (!tab[count])
				return (NULL);
			count++;
			tmp = tmp->next;
			if (tmp)
				tok = tmp->content;
		}
		tab[count] = NULL;
		return (tab);
	}
}
