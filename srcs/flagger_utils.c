/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:28:45 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/10 11:45:04 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "flag.h"

void	set_flag(int *flag, int bit)
{
	*flag |= (1 << bit);
}

bool	get_flag(int *flag, int bit)
{
	if (*flag & (1 << bit))
		return (true);
	else
		return (false);
}

void	print_flags(int *flag)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (get_flag(flag, i))
		{
			ft_putnbr_fd(i, STDERR_FILENO);
			ft_putendl_fd(" : flag is set", STDERR_FILENO);
		}
		i++;
	}
}
