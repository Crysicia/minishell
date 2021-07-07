/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:10:21 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/07 14:43:36 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	copy_double_quoted_text(char **str, char **buffer)
{
	char	*expanded;
	char	*swap;
	char	*start;
	
	*str += 1; //moving over opening quot
	expanded = ft_calloc(count_expanded_len(*str) + 1, sizeof(char));
	if (!expanded)
		display_error(MSG_MALLOC_FAILED, NULL);
	start = expanded;
	while (**str && **str != '"')
	{
		if (**str == '$')
		{
			copy_env_var_to_buffer(str, expanded);
			while (*expanded)
				expanded++;
		}
		else
		{
			*expanded = **str;
			*str += 1;
			expanded++;
		}
	}
	swap = ft_strjoin(*buffer, start);
	free(*buffer);
	free(start);
	*buffer = swap;
	*str += 1;
}

char	*get_variable_name2(char *str)
{
	char	*var_name;
	size_t	index;

	index = 1;
	while (str[index] && ft_isalnum(str[index]))
		index++;
	var_name = ft_strndup(str + 1, index - 1);
	return (var_name);
}

int	count_expanded_len(char *str)
{
	int		i;
	int		len;
	char	*name;
	t_dict	*env_var;

	i = 0;
	len = 0;
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			name = get_variable_name2(str + i);
			if (name)
			{
				env_var = ft_getenv(name);
				if (env_var)
				{
					i += ft_strlen(name);
					len += ft_strlen(env_var->value) - 1;
				}
				free(name);
			}
			else
				display_error(MSG_MALLOC_FAILED, NULL);
		}
		i++;
		len++;
	}
	return (len);
}

void	copy_env_var_to_buffer(char **str, char *buffer)
{
	char	*var_name;
	t_dict	*env_var;
	char	*to_copy;

	var_name = get_variable_name(str);
	if (var_name)
	{
		env_var = ft_getenv(var_name);
		if (env_var)
		{
			to_copy = env_var->value;
			while (*to_copy)
			{
				*buffer = *to_copy;
				to_copy++;
				buffer++;
			}
			*buffer = 0;
		}
		free(var_name);
	}
}
