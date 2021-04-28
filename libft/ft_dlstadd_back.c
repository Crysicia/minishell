/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:05:53 by crysicia          #+#    #+#             */
/*   Updated: 2021/04/28 18:28:33 by crysicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	if (!new)
		return ;
	if (!*alst)
	{
		(*alst) = new;
		return ;
	}
	if (!(*alst)->next)
	{
		(*alst)->next = new;
		new->previous = *alst;
		return ;
	}
	ft_dlstadd_back(&((*alst)->next), new);
}
