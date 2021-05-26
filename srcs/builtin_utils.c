/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:31:24 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/14 15:24:36 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	display_error(char *command, char *custom)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	if (custom)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(custom, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
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
