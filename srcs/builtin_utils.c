/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:31:24 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/05 19:25:51 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	display_error(char *command, char *custom)
{
	int		i;
	char	buffer[256];
	char	*first;
	
	ft_bzero(&buffer[0], 256);
	first = "minishell:  ";
	i = ft_strlcpy(&buffer[0], first, ft_strlen(first) + 1);
	i += ft_strlcpy(&buffer[i - 1], command, ft_strlen(command) + 1);
	if (custom)
	{
		i += ft_strlcpy(&buffer[i - 1], ": ", 3);
		i += ft_strlcpy(& buffer[i - 1], custom, ft_strlen(custom) + 1);
	}
	buffer[i - 1] = '\n';
	write(2, buffer, ft_strlen(buffer));
}

bool	is_env_valid(char *env, bool can_contain_eq)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[0]))
		return (false);
	while ((ft_isalnum(env[i]) || env[i] == '_') && env[i] != '=')
		i++;
	if (i > 0 && (!env[i] || ft_isspace(env[i])
			|| (env[i] == '=' && can_contain_eq)))
		return (true);
	return (false);
}
