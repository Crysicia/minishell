/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:36:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/06 19:16:09 by pcharton         ###   ########.fr       */
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
		else if (*str == '\'')
			copy_simple_quoted_text(&str, &buffer);
//		else if (*str == '"')
//			copy_double_quoted_text(&str, &buffer);
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
	while (*(*str + index) && ft_isalnum(*(*str + index)))
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
	{
		**buffer = '$';
		*buffer += 1;
	}
	free(name);
	name = NULL;
}
