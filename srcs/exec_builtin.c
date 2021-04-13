/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:02:14 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/13 13:40:11 by lpassera         ###   ########.fr       */
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
