/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 23:01:22 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/07 23:01:22 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scanner.h"
#include <string.h>

char	*ft_strndup(char *str, size_t n)
{
	char	*result;

	result = malloc(sizeof(char) * (n + 1));
	if (result)
	{
		strncpy(result, str, n);
		result[n] = 0;
	}
	return (result);
}

/* to be destroyed */
bool	is_valid_command(char *line)
{
	int		letter;

	letter = 0;
	while (line[letter]
		&& is_allowed_character(line[letter]))
		letter++;
	if (letter)
		return (true);
	else
		return (false);
}

static int	awful_tmp_fct(char *line, int *letter, int *start, int *to_end)
{
	int	count;

	*letter = 0;
	*start = 0;
	*to_end = 0;
	count = 1;
	while (line[*to_end] && ft_is_lowercase(line[*to_end]))
		(*to_end) += 1;
	*letter = *to_end;
	while (line[*letter] && is_allowed_character(line[*letter]))
		(*letter) += 1;
	if (*letter > *to_end)
		count++;
	return (count);
}

char	**evaluate_command(char *line)
{
	int		letter;
	int		count;
	int		start;
	int		to_end;
	char	**tab;

	count = awful_tmp_fct(line, &letter, &start, &to_end);
	tab = malloc(sizeof(char *) * (count + 1));
	if (tab)
	{
		tab[0] = ft_strndup(line, to_end);
		if (count == 2)
		{
			start = to_end;
			to_end = letter;
			while (is_space(line[start]) && (start < to_end))
				start++;
			tab[1] = ft_strndup(&line[start], to_end - start);
		}
		tab[count] = NULL;
	}
	return (tab);
}
