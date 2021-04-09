/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:47:07 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/09 16:14:31 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

size_t ft_arrlen(char **arr)
{
	size_t size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

bool ft_are_all_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
			return (false);
		str++;
	}
	return (true);
}

void builtin_exit(t_command *command)
{
	size_t args_size;

g_last_exit_code = 0;
	args_size = ft_arrlen(command->args);
	if (args_size == 1)
		exit(g_last_exit_code);
	if (args_size >= 2)
	{
		if (!ft_are_all_numeric(command->args[1]))
		{
			printf("exit: %s: numeric argument required\n", command->args[1]);
			g_last_exit_code = 2;
		}
		else if (args_size > 2)
		{
			g_last_exit_code = 1;
			printf("exit: too many arguments\n");
			return ;
		}
		else
			g_last_exit_code = ft_atoi(command->args[1]);
	}
	exit(g_last_exit_code);
}
