/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:48:01 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/10 11:45:47 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "flag.h"
#include "../libft/libft.h"

void	word_flagger(t_token *token)
{
	if (token->role == word)
		flag_quoting(token->cmd, &token->flag);
	flag_expansion(token->cmd, &token->flag);
}

void	flag_quoting(char *token_str, int *flag)
{
	while (token_str && *token_str)
	{
		if ((*token_str == '\'' || *token_str == '"')
			&& is_quote_closed(*token_str, token_str))
			token_str = flag_next_quote(*token_str, flag, token_str + 1);
		else
			token_str++;
	}
	if (!get_flag(flag, _SINGLE_QUOTES) && !get_flag(flag, _DOUBLE_QUOTES))
		set_flag(flag, _NO_QUOTES);
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
			set_flag(flagged, _SINGLE_QUOTES);
		else if (quote == '"')
			set_flag(flagged, _DOUBLE_QUOTES);
		return (ptr);
	}
	else
		return (NULL);
}

void	flag_expansion(char *token_str, int *flag)
{
	char	*word;
	char	quote;

	word = token_str;
	quote = 0;
	while (word && *word)
	{
		if (*word == '"' && !quote)
			quote = '"';
		else if (*word == '"' && quote == '"')
			quote = 0;
		if (*word == '\'' && !quote && is_quote_closed(*word, word))
		{
			word++;
			while (*word != '\'')
				word++;
		}
		if (*word && *word == '$')
		{
			set_flag(flag, _EXPANSION);
			break ;
		}
		word++;
	}
}
