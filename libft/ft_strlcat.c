/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 12:20:27 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:48:45 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	index;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	index = 0;
	if (dstsize == 0)
		return (srclen);
	if (dstsize == dstlen)
		return (srclen + dstlen);
	if (dstsize < dstlen)
		return (dstsize + srclen);
	while (index + dstlen < dstsize - 1 && src[index])
	{
		dst[dstlen + index] = src[index];
		index++;
	}
	dst[dstlen + index] = '\0';
	return (srclen + dstlen);
}
