/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:36:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/04 15:12:47 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "flag.h"

char	*expand_text(char *str)
{
	char	*buffer;

	buffer = ft_strdup("");
	if (!buffer)
		display_error(MSG_MALLOC_FAILED, NULL);
	while (*str)
	{
		if (*str == '$')
			expand_env_variable(&str, &buffer);
		else if (*str == '\'' && is_quote_closed(*str, str))
			copy_simple_quoted_text(&str, &buffer);
		else if (*str == '"' && is_quote_closed(*str, str))
			copy_double_quoted_text(&str, &buffer);
		else
			copy_unquoted_text(&str, &buffer);
	}
	return (buffer);
}

char	*get_variable_name(char **str)
{
	char	*var_name;
	size_t	index;

	index = 1;
	while (*(*str + index)
			&& (ft_isalnum(*(*str + index)) || *(*str + index) == '_'))
		index++;
	var_name = ft_strndup(*str + 1, index - 1);
	*str += index;
	return (var_name);
}

void	expand_exit_status(char **str, char **buffer)
{
	char	*exit_status;

	exit_status = ft_itoa((unsigned char)g_globals->status);
	ft_strlcpy(*buffer, exit_status, ft_strlen(exit_status) + 1);
	*str += 1;
	free(exit_status);
	exit_status = NULL;
}

void	expand_env_variable(char **str, char **buffer)
{
	t_dict	*env_var;
	char	*name;
	char	*tmp;

	name = get_variable_name(str);
	if (name && *name)
	{
		env_var = ft_getenv(name);
		if (env_var && *buffer)
		{
			tmp = ft_strjoin(*buffer, env_var->value);
			free(*buffer);
			*buffer = tmp;
		}
	}
	else if (**str == '?')
		expand_exit_status(str, buffer);
	else
		add_a_dollar(buffer);
	free(name);
	name = NULL;
}

void	add_a_dollar(char **buffer)
{
	char	*to_free;
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	to_free = *buffer;
	*buffer = ft_strjoin(*buffer, tmp);
	free(tmp);
	if (!*buffer)
	{
		free(to_free);
		ft_exit_with_error_msg(MSG_MALLOC_FAILED);
	}
	free(to_free);
}
