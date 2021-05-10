/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:16:09 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/30 11:16:09 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

bool	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

bool	is_escape_character(char chr)
{
	if (chr == '"' || chr == '\'' || chr == '\\')
		return (1);
	else
		return (0);
}

bool	is_operator(char *str)
{
	if ((*str == ';') || (*str == '|') || (*str == '<') || (*str == '>')
		|| !ft_strncmp(str, ">>", 2))
		return (1);
	else
		return (0);
}

bool	is_redirection(char *str)
{
	if ((*str == '<') || (*str == '>') || !ft_strncmp(str, ">>", 2))
		return (1);
	else
		return (0);
}
