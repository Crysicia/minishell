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
#include "../libft/libft.h"

int	check_quoting(char *word)
{
	int		flag;
	int		quote_count;

	flag = 0;
	quote_count = 0;
	while (word && *word)
	{
		if ((*word == '\'') || (*word == '\"'))
		{
			if (*word == '\'')
				word = flag_next_single_quote(&flag, ++word);
			else if (*word == '\"')
				word = flag_next_unescaped_double_quote(&flag, ++word);
			update_flag_count(&flag, &quote_count);
		}
		else if (*word == '\\')
			word++;
		if (word)
			word++;
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
		if ((str[index] == '\"') && (!escaped))
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
