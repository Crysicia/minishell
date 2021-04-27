/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:45:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/27 22:32:08 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>

typedef struct      s_btree
{
    struct  s_btree *left;
    struct  s_btree *right;
    void            *item;
}                   t_btree;

t_btree *btree_create_node(void *item);
void    btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void    btree_apply_infix(t_btree *root, void (*applyf)(void *));
void    btree_apply_suffix(t_btree *root, void (*applyf)(void *));

#endif
