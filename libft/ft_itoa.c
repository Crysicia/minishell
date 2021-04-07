/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 21:27:22 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:43:59 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_length_forecast(int n)
{
	size_t	length;

	length = 1;
	if (n < 0)
		length++;
	n /= 10;
	while (n)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	length;

	length = ft_length_forecast(n);
	if (n == 0)
		return (ft_strdup("0"));
	str = malloc(1 + length * sizeof(char));
	if (str)
	{
		str[length--] = '\0';
		if (n < 0)
			str[0] = '-';
		while (n != 0)
		{
			str[length] = (n % 10) + '0';
			if (n < 0)
				str[length] = -(n % 10) + '0';
			n /= 10;
			length--;
		}
	}
	return (str);
}
