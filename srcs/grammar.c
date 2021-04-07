/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:56:28 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/06 22:56:28 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

int ft_strcmp(char *dst, char *src)
{
    while (*dst && *src && (*dst == *src))
    {
        src++;
        dst++;
    }
    return (*dst - *src);
}

int is_a_command(t_word *word)
{
    if (ft_strcmp(word->token, "echo") == 0)
    {
        word->role = command;
        return (0);
    }
    else if (ft_strcmp(word->token, "env") == 0)
    {
        word->role = command;
        return (0);
    }
    else
        return (-1);
}
