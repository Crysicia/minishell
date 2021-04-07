/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:52:10 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:30:31 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && 13 >= c) || c == 32);
}

int	ft_atoi(const char *str)
{
	long	total;
	int		sign;
	size_t	index;

	total = 0;
	sign = POSITIVE;
	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = NEGATIVE;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		total *= 10;
		total += str[index] - '0';
		index++;
	}
	return (total * sign);
}
