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
	int		quote_count;

	ptr = word;
	flag = 0;
	quote_count	= 0;
	while (ptr && *ptr)
	{
		if (*ptr == '\'')
			ptr = flag_next_single_quote(&flag, ++ptr);
		else if (*ptr == '"')
			ptr = flag_next_unescaped_double_quote(&flag, ++ptr);
		else if (*ptr == '\\')
			ptr++;
		update_flag_count(&flag, &quote_count);
		if (ptr)
			ptr++;
		else
			return (QUOTING_ERROR);
	}
	if (quote_count >= 2)
		flag = MIXED_QUOTES;
	return (flag);
}

char	*flag_next_single_quote(int	*flagged, char *word)
{
	char	*ptr;
			
	ptr = word;
	while (*ptr && *ptr != '\'')
		ptr++;
	if (*ptr)
	{
		*flagged = SINGLE_QUOTES;
		return (ptr);
	}
	else
		return (NULL);
}

char	*flag_next_unescaped_double_quote(int *flagged, char *str)
{
	size_t	index;
	bool	escaped;

	index = 0;
	escaped = false;
	while (str[index])
	{
		if (str[index] == '"' && !escaped)
		{
			*flagged = DOUBLE_QUOTES;
			return (&str[index]);
		}
		if (str[index] == '\\')
			escaped = !escaped;
		else
			escaped = false;
		index++;
	}
	return (NULL);
}

void	update_flag_count(int *flag, int *count)
{
	if (!(*count) && (*flag))
		*count += 1;
	else if ((*count) && (*flag))
	{
		*count += 1;
		*flag = 0;
	}
}