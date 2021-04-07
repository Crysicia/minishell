/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:35:53 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:50:10 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	size_t	s_len;

	index = -1;
	s_len = 0;
	while (s[s_len])
		s_len++;
	while (++index <= s_len)
		if (s[s_len - index] == (char)c)
			return ((char *)&s[s_len - index]);
	return (NULL);
}
