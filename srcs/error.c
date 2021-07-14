/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:36:53 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/14 13:47:01 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	parser_error(t_token *tok)
{
	ft_putstr_fd("Minishell : unexpected syntax error near `", STDERR_FILENO);
	ft_putstr_fd(tok->cmd, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (-1);
}

void	display_error(char *command, char *custom)
{
	int		i;
	char	buffer[256];
	char	*first;

	ft_bzero(&buffer[0], 256);
	first = "minishell:  ";
	i = ft_strlcpy(&buffer[0], first, ft_strlen(first) + 1);
	i += ft_strlcpy(&buffer[i - 1], command, ft_strlen(command) + 1);
	if (custom)
	{
		i += ft_strlcpy(&buffer[i - 1], ": ", 3);
		i += ft_strlcpy(& buffer[i - 1], custom, ft_strlen(custom) + 1);
	}
	buffer[i - 1] = '\n';
	write(2, buffer, ft_strlen(buffer));
}
