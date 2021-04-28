/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:25:00 by crysicia          #+#    #+#             */
/*   Updated: 2021/04/28 14:05:15 by crysicia         ###   ########.fr       */
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
	while (*arguments)
	{
		if (!is_env_valid(*arguments, false))
			return (unset_error(*arguments, ERR_BUILTIN_FAILED));
		ft_unsetenv(*arguments);
		arguments++;
	}
	return (SUCCESS);
}
