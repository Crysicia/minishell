/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:47:20 by crysicia          #+#    #+#             */
/*   Updated: 2021/04/28 18:27:56 by crysicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlstsize(t_dlist *lst)
{
	if (!lst)
		return (0);
	return (1 + ft_dlstsize(lst->next));
}
