/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:48:01 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/05 11:48:01 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/flag.h"

void	word_flagger(t_token *token)
{
	if (token->role == word)
	{
		token->flag = check_quoting(token->cmd);
	}
}

int	check_quoting(char *word)
{
	char	*ptr;
	int		flag;

	ptr = word;
	flag = 0;
	while (*ptr)
	{
		if (*ptr == '\'')
		{
			flag = SINGLE_QUOTES;
			ptr = find_next_single_quote(++ptr);
		}
		else if (*ptr == '"')
		{
			flag = DOUBLE_QUOTES;
			ptr = go_to_next_unescaped_char(++ptr, '"');
		}
		else if (*ptr == '\\')
			ptr++;
		if (ptr)
			ptr++;
		else
			return (QUOTING_ERROR);
	}
	return (flag);
}

char	*find_next_single_quote(char *word)
{
	char	*ptr;

	ptr = word;
	while (*ptr && *ptr != '\'')
		ptr++;
	if (*ptr)
		return (ptr);
	else
		return (NULL);
}

char *go_to_next_unescaped_char(char *str, char target)
{
	size_t index;
	bool escaped;

	index = 0;
	escaped = false;
	while (str[index])
	{
		if (str[index] == target && !escaped)
			return (&str[index + 1]);
		if (str[index] == '\\')
			escaped = !escaped;
		else
			escaped = false;
		index++;
	}
	return (NULL);
}