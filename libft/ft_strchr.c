/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:35:53 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:47:45 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	index;
	size_t	s_len;

	index = -1;
	s_len = 0;
	while (s[s_len])
		s_len++;
	while (++index <= s_len)
		if (s[index] == (char)c)
			return ((char *)&s[index]);
	return (NULL);
}
