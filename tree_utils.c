/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:55:26 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/27 22:52:20 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree		*node;

	node = malloc(sizeof(t_btree));
	if (node)
	{
		node->item = item;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		applyf(root->item);
		btree_apply_prefix(root->left, applyf);
		btree_apply_prefix(root->right, applyf);
	}
}

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		btree_apply_prefix(root->left, applyf);
		applyf(root->item);
		btree_apply_prefix(root->right, applyf);
	}
}

void	btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		btree_apply_prefix(root->left, applyf);
		btree_apply_prefix(root->right, applyf);
		applyf(root->item);
	}
}
