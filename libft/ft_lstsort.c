/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:22:01 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/22 14:33:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstswap_content(t_list *previous, t_list *current)
{
	void	*swap;

	swap = previous->content;
	previous->content = current->content;
	current->content = swap;
}

void	ft_lstsort(t_list **head, int (*cmp)())
{
	t_list	*previous;
	t_list	*node;
	int		sorted;

	if (!head || !*head)
		return ;
	sorted = 0;
	while (!sorted)
	{
		previous = NULL;
		node = *head;
		sorted = 1;
		while (node)
		{
			if (previous && cmp(previous->content, node->content) > 0)
			{
				lstswap_content(previous, node);
				sorted = 0;
			}
			previous = node;
			node = node->next;
		}
	}
}
