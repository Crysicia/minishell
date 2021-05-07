/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:36:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/29 15:50:00 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
void	expansion_flagger(char *str)
{
	if ()
}
*/

/*
  strcpy() before after $var
  check var (alphanumeric len, no \before)
  getenv(var)
  write in buffer while adding \ to \ and "

  remove quotes
  remove antislash

void	expand_env_variable(char *str, char *buffer)
{
	char	tmp;
	char	*env_var;
	size_t	index;

	index = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	tmp = str[i];
	str[i] = 0;
	env_var = ft_getenv(str);
	if (env_var)
		ft_strlcpy(buffer, env_var, ft_strlen(env_var));
}

 */

int	copy_single_quoted_text(char *str, char *buffer)
{
	char	*start;

	start = str;
	str++;
	while (*str && (*str != '\''))
	{
		if (*str == '\\')
			str++;
		str++;
	}
	if ((str - start) == (unsigned int)ft_strlen(start))
		return (-1);
	else
		return (ft_strlcpy(buffer, start, str - start));
}
