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

bool	is_space(int c)
{
	if ((c == ' ') || (c == '\t'))
		return (true);
	else
		return (false);
}
