/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:11:00 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:47:38 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcchr(const char *s, int c)
{
	size_t	index;
	size_t	s_len;

	index = -1;
	s_len = 0;
	while (s[s_len])
		s_len++;
	while (++index <= s_len)
		if (s[index] != (char)c)
			return ((char *)&s[index]);
	return (NULL);
}
