/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 10:52:22 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/01 18:32:41 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*deallocate_pipe_tab(int **tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(tab[i][0]);
		close(tab[i][1]);
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

int	**allocate_pipe_tab(int	nb)
{
	int	i;
	int	**tab;

	if (nb > 255)
		return (NULL);
	tab = malloc(sizeof(int *) * (nb + 1));
	if (tab)
	{
		i = 0;
		while (i < nb)
		{
			tab[i] = malloc(sizeof(int) * 2);
			if (!tab[i])
				return (deallocate_pipe_tab(tab, i));
			i++;
		}
		tab[i] = NULL;
	}
	return (tab);
}
