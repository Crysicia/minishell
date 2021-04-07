/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:32:37 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 14:01:22 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *str, char *set)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		while (ft_strchr(set, str[index]) && str[index])
			index++;
		if (!ft_strchr(set, str[index]) && str[index])
			count++;
		while (!ft_strchr(set, str[index]) && str[index])
			index++;
	}
	return (count);
}

static size_t	ft_word_len(char const *str, char *set)
{
	size_t	length;

	length = 0;
	while (!ft_strchr(set, str[length]) && str[length])
		length++;
	return (length);
}

char	**ft_split_set(char const *s, char *set)
{
	size_t	index;
	size_t	arr_i;
	char	**arr;

	index = 0;
	arr_i = 0;
	if (!s)
		return (NULL);
	arr = malloc((ft_count_words(s, set) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (arr_i < ft_count_words(s, set))
	{
		while (ft_strchr(set, s[index]))
			index++;
		arr[arr_i] = ft_substr(s, index, ft_word_len(&s[index], set));
		if (!arr[arr_i])
			return (ft_free_matrix((void **)arr, arr_i + 1));
		index += ft_word_len(&s[index], set);
		arr_i++;
	}
	arr[arr_i] = NULL;
	return (arr);
}
