/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 01:29:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/07 01:29:36 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/grammar.h"

t_word  *create_word(char *input)
{
	t_word  *new;

	new = malloc(sizeof(t_word));
	if (!new || !input)
		return (NULL);
	else
	{
		new->token = input;
		new->role = not_given;
	return (new);
	}
}

void    destroy_void(t_word *word)
{
    free(word->token);
    word->token = NULL;
    free(word);
    word = NULL;
}