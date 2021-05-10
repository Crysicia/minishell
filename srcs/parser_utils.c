/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 07:41:15 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 12:59:33 by pcharton         ###   ########.fr       */
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
		new->type = 0;
		new->words = NULL;
		new->redirections = NULL;
	}
	else
		display_error("Malloc failed", "new_simple_command function");
	return (new);
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

/*
void	destroy_simple_command(t_simple_command *to_destroy)
{

}
*/
