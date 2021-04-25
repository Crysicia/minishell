/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:02:14 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/25 16:21:25 by crysicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

bool	is_builtin(char *str)
{
	static char	*builtins[BUILTINS_NB] = {"cd", "echo",
		"env", "exit", "export", "pwd", "unset"};
	int			index;

	index = 0;
	while (index < BUILTINS_NB)
	{
		if (!ft_strcmp(builtins[index], str))
			return (true);
		index++;
	}
	return (false);
}

int	(*get_builtin(char *str))(char **arguments)
{
	static char	*builtins[BUILTINS_NB] = {"cd", "echo",
		"env", "exit", "export", "pwd", "unset"};
	static	int	(*builtins_array[BUILTINS_NB])(char **) = {NULL,
		NULL, builtin_env, NULL, builtin_export, builtin_pwd, NULL};
	int			index;

	index = 0;
	while (index < BUILTINS_NB)
	{
		if (!ft_strcmp(builtins[index], str))
			return (builtins_array[index]);
		index++;
	}
	return (NULL);
}

int	execute_builtin(char *str, char **arguments)
{
	int	(*builtin)(char **);

	builtin = get_builtin(str);
	if (!builtin)
		return (1);
	return (builtin(arguments));
}
