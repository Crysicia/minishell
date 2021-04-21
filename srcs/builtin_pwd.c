/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:54:01 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/21 12:13:28 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <limits.h>

int	builtin_pwd(t_command *command)
{
	char	*path;

	(void)command;
	path = getcwd(NULL, PATH_MAX);
	if (path)
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
	else
		return (-1);
}
