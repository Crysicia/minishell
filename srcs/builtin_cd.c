/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:01:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/26 16:56:08 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <sys/param.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

bool	change_pwd_vars(void)
{
	char	cwd[MAXPATHLEN];
	t_dict	*pwd;

	pwd = ft_getenv("PWD");
	if (!getcwd(cwd, MAXPATHLEN))
		return (false);
	ft_setenv("OLDPWD", pwd->value);
	ft_setenv("PWD", cwd);
	return (true);
}

int	builtin_cd(char **arguments)
{
	t_dict	*home;

	if (!arguments || !*arguments)
	{
		home = ft_getenv("HOME");
		if (!home)
			return (2);
		if (!chdir(home->value))
			return (!change_pwd_vars());
		return (1);
	}
	if (!chdir(arguments[0]) || !ft_strcmp(arguments[0], ""))
		return (!change_pwd_vars());
	return (1);
}
