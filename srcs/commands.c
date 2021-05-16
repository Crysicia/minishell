/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:38:46 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/15 14:38:46 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/parser.h"

t_simple_command	*new_simple_command(void)
{
	t_simple_command	*new;

	new = malloc(sizeof(t_simple_command));
	if (new)
	{
		new->words = NULL;
		new->redirections = NULL;
	}
	else
		display_error("Malloc failed", "new_simple_command function");
	return (new);
}

void	free_simple_command(void *to_free)
{
	t_simple_command	*ptr;

	ptr = to_free;
	ft_lstclear(&ptr->words, free_token);
	ft_lstclear(&ptr->redirections, free_redirection);
	free(ptr);
	ptr = NULL;
}

t_redirection	*new_redirection(void)
{
	t_redirection	*new;

	new = malloc(sizeof(t_redirection));
	if (new)
	{
		new->operator = NULL;
		new->file = NULL;
	}
	else
		display_error("Malloc failed", "new_simple_command function");
	return (new);
}

void	free_redirection(void *to_free)
{
	t_redirection	*ptr;

	ptr = to_free;
	free_token(ptr->operator);
	free_token(ptr->file);
	free(ptr);
	ptr = NULL;
}
