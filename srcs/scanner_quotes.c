/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:39:03 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/13 12:32:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scanner.h"
#include <stdio.h>

/*
** Shamelessly copy pasted from another minishell
** https://stackoverflow.com/questions/64539353/algo-to-check-that-a-string-doesnt-have-missing-close-quote-or/64556933
*/
bool are_quotes_valid(char *line)
{
	char inner_quote;
	char outer_quote;
	int index;

	if (!line)
		return false;
	index = 0;
	inner_quote = 0;
	outer_quote = 0;
	while (line[index])
	{
		if (ft_strchr("\"'", line[index]))
		{
			if (index > 0 && line[index - 1] == '\\')
				;
			else if (!outer_quote)
				outer_quote = line[index];
			else
			{
				if (outer_quote == line[index])
				{
					inner_quote = 0;
					outer_quote = 0;
				}
				else
				{
					if (inner_quote == line[index])
						inner_quote = 0;
					else
						inner_quote = line[index];
				}
			}
		}
		index++;
	}
	if (outer_quote)
		return (false);
	return (true);
}

// bool are_quotes_valid(char *line)
// {
// 	int	i;
// 	int	open;

// 	i = 0;
// 	open = 0;
// 	if (!line)
// 		return (false);
// 	while (line[i])
// 	{
// 		if (i > 0 && line[i - 1] == '\\')
// 			;
// 		else if (open == 0 && line[i] == '\"')
// 			open = 1;
// 		else if (open == 0 && line[i] == '\'')
// 			open = 2;
// 		else if (open == 1 && line[i] == '\"')
// 			open = 0;
// 		else if (open == 2 && line[i] == '\'')
// 			open = 0;
// 		i++;
// 	}
// 	return (!open);
// }

// bool are_quotes_valid(char *line)
// {
// 	int	simple_quotes;
// 	int	double_quotes;

// 	if (!line)
// 		return (false);
// 	simple_quotes = 0;
// 	double_quotes = 0;
// 	while (*line)
// 	{
// 		if (*line == '\'')
// 			simple_quotes++;
// 		else if (*line == '"')
// 			double_quotes++;
// 		line++;
// 	}
// }

// bool are_quotes_valid(char *line)
// {
// 	char	*single_start;
// 	char	*single_end;
// 	char	*double_start;
// 	char	*double_end;

// 	if (!line)
// 		return (false);
// 	single_start = ft_strchr(line, '\'');
// 	single_end = ft_strrch(line, '\'');
// 	if ()
// }
