/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:47:07 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/28 12:38:08 by crysicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	ft_are_all_numeric(char *str)
{
	if (!ft_strchr("0123456789-+", *str))
		return (false);
	str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	exit_error(char *argument, char *message, int code)
{
	char	buffer[MAXPATHLEN];

	g_globals->status = code;
	if (argument)
	{
		ft_strlcpy(buffer, argument, ft_strlen(argument));
		ft_strlcat(buffer, ": ", MAXPATHLEN);
	}
	ft_strlcat(buffer, message, MAXPATHLEN);
	display_error("exit", buffer);
	return (ERR_BUILTIN_FAILED);
}

int	builtin_exit(char **arguments)
{
	if (!arguments || !*arguments)
		exit(g_globals->status);
	else
	{
		if (!ft_are_all_numeric(*arguments))
			exit_error(*arguments, "numeric argument required", 2);
		else if (arguments[1])
			return (exit_error(NULL, "Too many arguments", ERR_BUILTIN_FAILED));
		else
			g_globals->status = ft_atoi(*arguments);
	}
	exit(g_globals->status);
	return (g_globals->status);
}
