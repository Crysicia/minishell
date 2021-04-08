/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 01:02:07 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/08 01:02:07 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scanner.h"

bool	ft_is_lowercase(int c)
{
	if ((c >= 'a') && (c <= 'z'))
		return (true);
	else
		return (false);
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
bool	is_space(int c)
{
	if ((c == ' ') || (c == '\t'))
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
/* To be destroyed */
bool 	is_allowed_character(int c)
{
	if (ft_is_lowercase(c)
		|| is_space(c))
		return (true);
	else
		return (false);
}
