/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:35:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/13 11:54:12 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int create_file(char *path, char *redirection_type)
{
	int fd;
	int open_flags;

	open_flags = O_CREATE;
	if (!ft_strcmp(redirection_type, ">>"))
		open_flags |= O_APPEND;
	fd = open(path. open_flags);
	return (fd);
}


int test_redirections(void)
{
	return 0;
}
