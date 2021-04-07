/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 15:14:57 by lpassera          #+#    #+#             */
/*   Updated: 2020/08/09 15:14:58 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	min;
	size_t	max;

	if (!s1 || !set)
		return (NULL);
	min = 0;
	max = ft_strlen(s1);
	while (ft_strchr(set, s1[min]) && s1[min])
		min++;
	while (ft_strchr(set, s1[max]) && max > 0 && max > min)
		max--;
	return (ft_substr(s1, min, max - min + 1));
}
