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

size_t	command_len(char *line)
{
	size_t	count;

	count = 0;
	count += keyword_len(line);
	while (option_len(&line[count]))
		count += option_len(&line[count]);
	count += argument_len(&line[count]);
	return (count);
}

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
	size_t	hyphen_count;

	count = 0;
	hyphen_count = 0;
	while (line[count]
		&& is_space(line[count]))
		count++;
	while (line[count + hyphen_count]
		&& (line[count + hyphen_count] == '-')
		&& (hyphen_count < 2))
		hyphen_count++;
	count += hyphen_count;
	while (line[count]
		&& ft_is_lowercase(line[count]))
		count++;
	if (line[count]
		&& !is_space(line[count]) && !is_control_operator(line[count]))
		count = 0;
	else if (!ft_in_range(1, 2, hyphen_count))
		count = 0;
	return (count);
}

size_t	argument_len(char *line)
{
	size_t	count;

	count = 0;
	while (line[count]
		&& is_argument_character(line[count]))
		count++;
	return (count);
}
