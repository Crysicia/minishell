/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 19:35:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/11 08:39:52 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*	Should not change */

void	copy_unquoted_text(char **str, char **buffer)
{
	int		i;
	char	quote;
	char	*tmp;

	i = 0;
	while (*(*str + i) && (*(*str + i) != '$'))
	{
		if (((*(*str + i) == '"') || (*(*str + i) == '\''))
			&& is_quote_closed(*(*str + i), *str + i))
			break ;
		i++;
	}
	quote = *(*str + i);
	*(*str + i) = 0;
	tmp = ft_strjoin(*buffer, *str);
	if (!tmp)
		display_error(MSG_MALLOC_FAILED, NULL);
	free(*buffer);
	*buffer = tmp;
	*(*str + i) = quote;
	*str += i;
}

void	copy_simple_quoted_text(char **str, char **buffer)
{
	int		i;
	char	*tmp;
	char	save;

	i = 1;
	while (*(*str + i) != '\'')
		i++;
	save = *(*str + i + 1);
	*(*str + i + 1) = 0;
	tmp = ft_strjoin(*buffer, *str);
	if (!tmp)
		display_error(MSG_MALLOC_FAILED, NULL);
	free(*buffer);
	*buffer = tmp;
	*(*str + i + 1) = save;
	*str += i + 1;
}

void	remove_quoting(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if ((*str == '"' || *str == '\'') && is_quote_closed(*str, str))
		{
			quote = *str;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			while (*str != quote)
				str++;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
}
