/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:25:00 by crysicia          #+#    #+#             */
/*   Updated: 2021/04/29 16:22:59 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	unset_error(char *argument, int code)
{
	char	buffer[MAXPATHLEN];

	ft_strlcpy(buffer, "'", 2);
	ft_strlcat(buffer, argument, MAXPATHLEN);
	ft_strlcat(buffer, "': not a valid identifier", MAXPATHLEN);
	display_error("unset", buffer);
	return (code);
}

int	builtin_unset(char **arguments)
{
	int ret;

	ret = SUCCESS;
	while (*arguments)
	{
		if (is_env_valid(*arguments, false))
			ft_unsetenv(*arguments);
		else
			ret = unset_error(*arguments, ERR_BUILTIN_FAILED);
		arguments++;
	}
	return (ret);
}
