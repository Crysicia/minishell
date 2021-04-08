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

bool	is_control_operator(int c)
{
	if (c == ';')
		return (true);
	else
		return (false);
}

bool	is_redirection(int c)
{
	if ((c == '|') || (c == '>') || (c == '<'))
		return (true);
	else
		return (false);
}

bool 	is_keyword_character(int c)
{
	if (ft_is_lowercase(c)
		|| (c == '/') || (c == '.') || (c == '~'))
		return (true);
	else
		return (false);
}

bool	is_argument_character(int c)
{
	if (ft_isalnum(c)
		|| is_space(c) || (c == '='))
		return (true);
	else
		return (false);
}
