/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:10:21 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/07 12:17:22 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	copy_double_quoted_text(char **str, char **buffer)
{
	int		i;

	*str += 1; //moving over opening quote
	i = count_expanded_len(*str);
	printf("len in double quoted is [%d]\n", i);
	while (**str && **str != '"')
		*str += 1;
	*str += 1;
	(void)buffer;
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
		}
		i++;
		len++;
	}
	return (len);
}
