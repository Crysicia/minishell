/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:54:01 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/27 14:40:22 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <limits.h>

int	builtin_pwd(char **arguments)
{
	char	*path;

	(void)arguments;
	path = getcwd(NULL, PATH_MAX);
	if (path)
	{
		printf("%s\n", path);
		free(path);
		return (SUCCESS);
	}
	return (ERR_BUILTIN_FAILED);
}
