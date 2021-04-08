/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_len_fcts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:25:46 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/08 11:25:46 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scanner.h"

size_t	keyword_len(char *line)
{
	size_t	count;

	count = 0;
	while (line[count]
		&& is_keyword_character(line[count]))
		count++;
	return (count);
}

size_t	option_len(char *line)
{
	size_t	count;

	count = 0;
	while (line[count]
		&& (line[count] == '-'))
		count++;
	if (!count || (count > 2))
		return (0);
	else
	{
		while (line[count]
			&& ft_is_lowercase(line[count]))
			count++;
		if (line[count] && !ft_is_lowercase(line[count]))
			count = 0;
		return (count);
	}
}
