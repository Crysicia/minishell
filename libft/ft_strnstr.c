/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 12:44:17 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:49:51 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelen;
	size_t	haylen;
	size_t	index;

	needlelen = ft_strlen(needle);
	haylen = ft_strlen(haystack);
	index = 0;
	if (needlelen == 0)
		return ((char *)haystack);
	while ((index + needlelen - 1) < len && (index + needlelen - 1) < haylen)
	{
		if (haystack[index] == *needle)
			if (ft_strncmp(&haystack[index], needle, needlelen) == 0)
				return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
