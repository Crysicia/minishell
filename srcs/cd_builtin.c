/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:01:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/19 17:15:23 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <sys/param.h>
#include <unistd.h>
#include <errno.h>

int		change_directory(t_list **env_list, char *new_path)
{
	if (!new_path)
		return (-1);
	(void)*env_list;
	(void)new_path;
	return (0);
}

int		is_valid_path(char *path)
{
	(void)path;
	return 42;
}
