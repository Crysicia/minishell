/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:16:09 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/06 19:43:27 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

bool	is_escape_character(char chr)
{
	if (chr == '"' || chr == '\'')
		return (1);
	else
		return (0);
}

bool	is_operator(char *str)
{
	if (*str == '|')
		return (1);
	else
		return (0);
}

bool	is_redirection(char *str)
{
	char	*ptr;

	ptr = str;
	if ((ft_strlen(ptr) >= 2) && (!(ft_strncmp(ptr, ">>", 2))
			|| !(ft_strncmp(ptr, "<<", 2))))
		return (1);
	else if ((*ptr == '<') || (*ptr == '>'))
		return (1);
	else
		return (0);
}

t_tok_type	get_token_role(char *line)
{
	t_tok_type	role;

	if (is_operator(line))
		role = operator;
	else if (is_redirection(line))
		role = redirection;
	else
		role = word;
	return (role);
}
