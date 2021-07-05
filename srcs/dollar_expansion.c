/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:36:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/05 11:24:07 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "flag.h"

int	expand_text(char *buffer, char *str)
{
	while (*str)
	{
		if (*str == '$')
			expand_env_variable(&str, &buffer);
		else if (*str == '\'')
			copy_simple_quoted_text(&str, &buffer);
		else if (*str == '"')
			copy_double_quoted_text(&str, &buffer);
		else
			*buffer++ = *str++;
	}
	return (0);
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

	name = get_variable_name(str);
	if (name && *name)
	{
		env_var = ft_getenv(name);
		if (env_var)
		{
			ft_strlcpy(*buffer, env_var->value, ft_strlen(env_var->value) + 1);
			*buffer += ft_strlen(env_var->value);
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
