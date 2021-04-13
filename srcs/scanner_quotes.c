/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:39:03 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/13 13:37:05 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scanner.h"

bool	are_quotes_valid(char *line)
{
	char	outer_quote;
	int		index;

	if (!line)
		return (false);
	index = 0;
	outer_quote = 0;
	while (line[index])
	{
		if (ft_strchr("\"'", line[index]))
		{
			if (index > 0 && line[index - 1] == '\\')
				;
			else if (!outer_quote)
				outer_quote = line[index];
			else if (outer_quote == line[index])
				outer_quote = 0;
		}
		index++;
	}
	if (outer_quote)
		return (false);
	return (true);
}
