/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:02:14 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/23 15:35:57 by lpassera         ###   ########.fr       */
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
		if (ft_strcmp(builtins[index], str) == 0)
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
		NULL, builtin_env, NULL, NULL, builtin_pwd, NULL};
	int			index;

	index = 0;
	while (index < BUILTINS_NB)
	{
		if (ft_strcmp(builtins[index], str) == 0)
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
