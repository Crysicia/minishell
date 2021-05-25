/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 18:21:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/10 13:04:28 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
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
		return ;
	}
	ft_lstadd_back(&((*alst)->next), new);
}
