/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:31:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/15 14:31:54 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "token.h"

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

char	**command_format(t_list *list)
{
	t_list	*tmp;
	t_token	*tok;
	size_t	index;
	size_t	count;
	char	**tab;

	index = count_command_words(list);
	tab = malloc((index + 1) * sizeof(char **));
	if (!tab)
		ft_malloc_error();
	tmp = list;
	count = 0;
	while (count < index)
	{
		tok = tmp->content;
		tab[count] = ft_strdup(tok->cmd);
		count++;
		tmp = tmp->next;
	}
	tab[count] = NULL;
	return (tab);
}
