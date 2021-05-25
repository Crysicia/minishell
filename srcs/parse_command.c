/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:31:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:36:20 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/token.h"

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

	count = 0;
	tab = NULL;
	if (check_command_syntax(list))
	{
		index = count_command_words(list);
		tab = malloc((index + 1) * sizeof(char **));
		if (!tab)
			ft_malloc_error();
		tmp = list;
		while (count < index)
		{
			tok = tmp->content;
			tab[count] = ft_strdup(tok->cmd);
			count++;
			tmp = tmp->next;
		}
		tab[count] = NULL;
	}
	return (tab);
}
