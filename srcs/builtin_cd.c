/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:01:31 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/21 12:48:53 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <sys/param.h>
#include <unistd.h>
#include <errno.h>

int	builtin_cd(char *new_path)
{
	if (!new_path)
		return (-1);
	(void)new_path;
	return (0);
}

int	is_valid_path(char *path)
{
	(void)path;
	return (42);
}
