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
bool	is_an_option(char *str)
{
	if (str && (((!ft_strncmp(str, "-", 1)) || (!ft_strncmp(str, "--", 2)))
			&& ft_strncmp(str, "---", 3)))
		return (true);
	else
		return (false);
}

bool	check_echo_option(char *str)
{
	if (is_an_option(str))
	{
		while (*str && (*str == '-'))
			str++;
		while (*str && (*str == 'n'))
			str++;
		if (!(*str))
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

int	builtin_echo(char **arguments)
{
	char	**ptr;
	bool	n_option;

	n_option = false;
	if (arguments)
	{
		ptr = arguments;
		while (*ptr)
		{
			if (check_echo_option(*ptr))
				n_option = true;
			else
			{
				char *tmp = ft_strtrim(*ptr, " \t");
				ft_putstr_fd(tmp, 1);
				if (*(ptr + 1))
					write(1, " ", 1);
			}
			ptr++;
		}
	}
	if (!n_option)
		printf("\n");
	return (0);
}
