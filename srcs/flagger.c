/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:48:01 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/19 14:29:27 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "flag.h"
#include "../libft/libft.h"

void	word_flagger(t_token *token)
{
	if (token->role == word)
		token->flag = check_quoting(token->cmd);
	if (!token->flag)
		token->flag = flag_expansion(token->cmd);
}

int	check_quoting(char *token_str)
{
	int		flag;

	flag = 0;
	while (token_str && *token_str)
	{
		if ((*token_str == '\'') || (*token_str == '\"'))
			token_str = flag_next_quote(*token_str, &flag, token_str + 1);
		else
			token_str++;
		if (token_str)
			token_str++;
		else
			return (0);
	}
	return (flag);
}

char	*flag_next_quote(char quote, int *flagged, char *word)
{
	char	*ptr;

	ptr = word;
	while (*ptr && *ptr != quote)
		ptr++;
	if (*ptr)
	{
		if (quote == '\'')
			*flagged = SINGLE_QUOTES;
		else if (quote == '"')
			*flagged = DOUBLE_QUOTES;
		return (ptr);
	}
	else
		return (NULL);
}

int	flag_expansion(char *token_str)
{
	char	*word;

	word = token_str;
	while (word && *word)
	{
		if (*word == '$')
			return (TO_EXPAND);
		else
			word++;
	}
	return (0);
}
