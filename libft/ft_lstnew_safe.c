/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:35:03 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/23 13:35:21 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_safe(void *content, void (*del)(void *))
{
	t_list	*list;

	list = ft_lstnew(content);
	if (!list)
		del(content);
	return (list);
}
