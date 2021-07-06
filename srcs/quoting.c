/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 19:35:30 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/06 19:30:45 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	remove_mixed_quotes(t_token *token)
{
	char	*buffer;
	char	*to_eval;

	printf("token flag is %x\n", token->flag);
	to_eval = token->cmd;
	buffer = expand_text(to_eval);

	printf("expanded is [%s]\n", buffer);
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
	puts(tmp);
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

/*
void	copy_double_quoted_text(char **str, char **buffer)
{
	int		i;
	char	*tmp;

	i = 1;
	while (*(*str + i) && (*(*str + i) != '"'))
	{
		i++;
		if (*(*str + i) == '$')
		{
			*(*str + i )
			tmp = ft_strjoin
			expand_env_variable(str, buffer);
		}
	}
	*str += 1;
}
*/
