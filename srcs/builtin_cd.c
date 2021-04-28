/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:01:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/27 15:13:37 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	cd_error(char *path, int code)
{
	char	buffer[MAXPATHLEN];

	ft_strlcpy(buffer, path, ft_strlen(path) + 1);
	ft_strlcat(buffer, ": ", MAXPATHLEN);
	ft_strlcat(buffer, strerror(errno), MAXPATHLEN);
	display_error("cd", buffer);
	return (code);
}

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
			return (ERR_ENV_NOT_FOUND);
		if (!chdir(home->value))
			return (!change_pwd_vars());
		return (cd_error(home->value, ERR_BUILTIN_FAILED));
	}
	if (!chdir(arguments[0]) || !ft_strcmp(arguments[0], ""))
		return (!change_pwd_vars());
	return (cd_error(arguments[0], ERR_BUILTIN_FAILED));
}
