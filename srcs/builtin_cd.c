/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:01:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/15 11:27:58 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*join_buffer(char *buffer, size_t buffer_size, char *s1, char *s2)
{
	ft_strlcpy(buffer, s1, ft_strlen(s1) + 1);
	ft_strlcat(buffer, s2, buffer_size);
	return (buffer);
}

int	cd_error(char *message, bool display_errno, int code)
{
	char	buffer[MAXPATHLEN];

	ft_strlcpy(buffer, message, ft_strlen(message) + 1);
	if (display_errno)
	{
		ft_strlcat(buffer, ": ", MAXPATHLEN);
		ft_strlcat(buffer, strerror(errno), MAXPATHLEN);
	}
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
	t_dict	*dict;
	char	*env;
	char	buffer[MAXPATHLEN];

	if (!arguments || !*arguments || !ft_strcmp(*arguments, "-"))
	{
		env = "HOME";
		if (arguments && *arguments && !ft_strcmp(*arguments, "-"))
			env = "OLDPWD";
		dict = ft_getenv(env);
		if (!dict)
			return (cd_error(join_buffer(buffer, MAXPATHLEN, env, " not set"),
					false, ERR_ENV_NOT_FOUND));
		if (!chdir(dict->value))
			return (!change_pwd_vars());
		return (cd_error(dict->value, true, ERR_BUILTIN_FAILED));
	}
	if (!chdir(arguments[0]) || !ft_strcmp(arguments[0], ""))
		return (!change_pwd_vars());
	return (cd_error(arguments[0], true, ERR_BUILTIN_FAILED));
}
