/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:24:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/06 14:37:43 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	else
	{
		while (str[i])
		{
			if (str[i] == c)
				return (++i);
			else
				i++;
		}
		return (0);
	}
}

size_t	gnl_strlen(char *str, int value)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	if (value == 1)
	{
		while (str && *str && *str != '\n')
		{
			len++;
			str++;
		}
	}
	else
	{
		while (str && *str)
		{
			len++;
			str++;
		}
	}
	return (len);
}

char	*gnl_strdup(char *str, int value)
{
	char	*dup;
	char	*result;

	dup = malloc(sizeof(dup) * (gnl_strlen(str, value) + 1));
	if (dup == NULL)
		return (NULL);
	else
	{
		result = dup;
		if (value == 1)
		{
			while (str && *str && *str != '\n')
				*dup++ = *str++;
		}
		else
		{
			while (str && *str)
				*dup++ = *str++;
		}
		*dup = '\0';
		return (result);
	}
}

char	*gnl_join(char *s1, char *s2)
{
	char	*join;
	char	*result;

	join = malloc(gnl_strlen(s1, 0) + gnl_strlen(s2, 1) + 1);
	if (join == NULL)
		return (NULL);
	else
	{
		result = join;
		while (s1 && *s1)
			*join++ = *s1++;
		while (*s2 && *s2 != '\n')
			*join++ = *s2++;
		*join = '\0';
		return (result);
	}
}

void	gnl_strcpy_and_fill(char *dest, char *source)
{
	size_t	i;

	i = 0;
	while (*source)
		dest[i++] = *source++;
	while (i < BUFFER_SIZE + 1)
		dest[i++] = '\0';
}
