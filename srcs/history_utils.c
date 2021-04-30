/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:01:00 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/30 17:15:26 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	add_to_history(char *line)
{
	char	*dup;
	t_dlist	*node;

	dup = ft_strdup(line);
	if (!dup)
		return (ERR_MALLOC_FAILED);
	node = ft_dlistnew(dup);
	if (!node)
	{
		free(dup);
		return (ERR_MALLOC_FAILED);
	}
	ft_dlstadd_back(&g_globals->history, node);
	return (SUCCESS);
}
