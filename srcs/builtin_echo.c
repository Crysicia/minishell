/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:17:18 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/20 12:43:09 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	builtin_echo(char **arguments)
{
	char	**ptr;
	int		ret;

	if (arguments)
	{
		ptr = arguments;
		while (*ptr)
			printf("%s\n", *ptr++);

	}
	ret = 0;
	(void)ret;
	(void)arguments;

	return (0);
}
