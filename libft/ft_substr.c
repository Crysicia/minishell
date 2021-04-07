/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:29:10 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 13:50:36 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub_len = ft_strlen(&s[start]);
	if (sub_len > len)
		sub_len = len;
	str = malloc((sub_len + 1) * sizeof(char));
	if (str)
		ft_strlcpy(str, &s[start], sub_len + 1);
	return (str);
}
