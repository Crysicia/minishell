/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:14:13 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/17 19:14:13 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_tabdup(char *tab[])
{
	char	**dup;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (*(tab + len))
		len++;
	dup = malloc(sizeof(char **) * (len + 1));
	while (i < len)
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[len] = NULL;
	return (dup);
}
