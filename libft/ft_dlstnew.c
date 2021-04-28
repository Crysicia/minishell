/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crysicia <crysicia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:35:55 by crysicia          #+#    #+#             */
/*   Updated: 2021/04/28 17:36:41 by crysicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*node;

	node = malloc(sizeof(t_dlist));
	if (node)
	{
		node->content = content;
		node->previous = NULL;
		node->next = NULL;
	}
	return (node);
}
