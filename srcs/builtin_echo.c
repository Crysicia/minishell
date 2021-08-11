/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:17:18 by lpassera          #+#    #+#             */
/*   Updated: 2021/08/11 12:20:43 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

bool	is_an_option(char *str)
{
	if (str && (!ft_strncmp(str, "-", 1)))
		return (true);
	else
		return (false);
}

bool	check_echo_option(char *str)
{
	if (is_an_option(str))
	{
		if (*str && (*str == '-'))
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

void	print_arguments(char **arguments)
{
	char	**ptr;

	ptr = arguments;
	while (*ptr)
	{
		ft_putstr_fd(*ptr, 1);
		if (*(ptr + 1))
			ft_putchar_fd(' ', 1);
		ptr++;
	}
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
			{
				ptr++;
				n_option = true;
			}
			else
				break ;
		}
		print_arguments(ptr);
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (0);
}
