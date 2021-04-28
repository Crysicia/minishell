/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:09:55 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/26 14:30:42 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

bool	is_absolute_path(char *path)
{
	if (!path)
		return (false);
	return (*path == '/');
}

bool	is_path(char *path)
{
	if (!path)
		return (false);
	return (!!ft_strchr(path, '/'));
}
