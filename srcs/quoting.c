/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 19:35:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/07 11:10:35 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	remove_mixed_quotes(t_token *token)
{
	char	*buffer;
	char	*to_eval;

	to_eval = token->cmd;
	buffer = expand_text(to_eval);
	free(token->cmd);
	token->cmd = ft_strdup(buffer);
	if (!token->cmd)
		ft_exit_with_error_msg(strerror(errno));
	free(buffer);
	buffer = NULL;
	return (1);
}

void	copy_unquoted_text(char **str, char **buffer)
{
	int		i;
	char	quote;
	char	*tmp;

	i = 0;
	while (*(*str + i) && (*(*str + i) != '\'')
			&& (*(*str + i) != '"') && (*(*str + i) != '$'))
		i++;
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

	i = 1;
	while (*(*str + i) && (*(*str + i) != '\''))
		i++;
	*(*str + i) = 0;
	tmp = ft_strjoin(*buffer, *str + 1);
	if (!tmp)
		display_error(MSG_MALLOC_FAILED, NULL);
	free(*buffer);
	*buffer = tmp;
	*(*str + i) = '\'';
	*str += i + 1;
}
