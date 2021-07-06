/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:48:01 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/06 16:52:31 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "flag.h"
#include "../libft/libft.h"

int	check_quoting(char *word)
{
	int		flag;

	flag = 0;
	while (word && *word)
	{
		if ((*word == '\'') || (*word == '\"'))
		{
			word = flag_next_quote(*word, &flag, word + 1);
//			update_flag_count(&flag)
		}
		if (word)
			word++;
		else
			return (0);
	}
	return (flag);
}

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
