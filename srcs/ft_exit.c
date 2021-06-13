/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:06:01 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/26 08:06:01 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_exit_with_error_msg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_exit();
}

void	ft_exit(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	destroy_globals();
	exit(errno);
}
