/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:31:24 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/28 14:04:54 by crysicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
	while (ft_isalnum(env[i]) && env[i] != '=')
		i++;
	if (i > 0 && (!env[i] || ft_isspace(env[i])
			|| (env[i] == '=' && can_contain_eq)))
		return (true);
	return (false);
}
