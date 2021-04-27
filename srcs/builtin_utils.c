/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:31:24 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/27 16:09:13 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	display_error(char *command, char *custom)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	if (custom)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(custom, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
