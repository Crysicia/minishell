/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:01:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/19 17:15:23 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <sys/param.h>
#include <unistd.h>
#include <errno.h>

void	update_pwd(t_list *env)
{
	(void)env;
}

void	update_oldpwd(t_list *env)
{
	(void)env;
}

int		cd_builtin(char *path)
{
	char	buffer[MAXPATHLEN];
	char	*cwd;

	ft_bzero(buffer, MAXPATHLEN);
	cwd = getcwd(buffer, MAXPATHLEN);
	if (!cwd || errno)
		return (-1);
	else
	{
		(void)path;
		free(cwd);
		return (0);
	}
}
