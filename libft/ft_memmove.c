/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:55:12 by lpassera          #+#    #+#             */
/*   Updated: 2020/08/04 17:55:13 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			index;
	unsigned char	*ptr_src;
	unsigned char	*ptr_dst;

	if (src == NULL && dst == NULL)
		return (NULL);
	index = -1;
	ptr_src = (unsigned char *)src;
	ptr_dst = (unsigned char *)dst;
	if (src > dst)
		while (++index < len)
			ptr_dst[index] = ptr_src[index];
	else
		while (++index < len)
			ptr_dst[len - index - 1] = ptr_src[len - index - 1];
	return (dst);
}
