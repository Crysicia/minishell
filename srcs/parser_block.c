/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:56:14 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:37:56 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_block	*new_block(void)
{
	t_block	*new;

	new = malloc(sizeof(t_block));
	return (new);
}

void	free_block(void *to_free)
{
	t_block	*ptr;

	ptr = to_free;
	if (ptr->id == simple_command)
		free_simple_command(ptr->kind.cmd);
	else if (ptr->id == pipeline)
		free_pipeline(ptr->kind.pipe);
	free(ptr);
	ptr = NULL;
}

void	set_block_ptr(t_block *block, void *ptr)
{
	if (block->id == simple_command)
		block->kind.cmd = ptr;
	else if (block->id == pipeline)
		block->kind.pipe = ptr;
}
