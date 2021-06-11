/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:48:01 by pcharton          #+#    #+#             */
/*   Updated: 2021/06/11 19:42:55 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "flag.h"
#include "../libft/libft.h"

char	*flag_next_quote(char quote, int *flagged, char *word)
{
	char	*ptr;

	ptr = word;
	while (*ptr && *ptr != quote)
		ptr++;
	if (*ptr)
	{
		if (quote == '\'')
			*flagged = SINGLE_QUOTES;
		else if (quote == '"')
			*flagged = DOUBLE_QUOTES;
		return (ptr);
	}
	else
		return (NULL);
}

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
			word = flag_next_quote(*word, &flag, word + 1);
			update_flag_count(&flag, &quote_count);
		}
		if (word)
			word++;
		else
			return (QUOTING_ERROR);
	}
	if (quote_count >= 2)
		flag = MIXED_QUOTES;
	return (flag);
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
