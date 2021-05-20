/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:36:53 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/19 15:13:00 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/header.h"
#include <errno.h>
#include <string.h>

void	ft_malloc_error(void)
{
	int		swap;
	char	*error;

	swap = errno;
	errno = ENOMEM;
	error = strerror(errno);
	printf("Malloc error %s_n", error);
	errno = swap;
}

void	syntax_error(void)
{
	printf("Minishell invalid token detected\n");
}

void	parser_error(int ret)
{
	if (ret == ERR_MALLOC_FAILED)
		display_error("Malloc failed", "parse_simple_command function");
	
}
