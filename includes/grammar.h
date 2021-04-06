/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:11:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/06 22:11:36 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_H
# define GRAMMAR_H
# include <stdlib.h>

enum e_role
{
    not_given = 0,
    command = 1,
    argument = 2,
    redirection = 3,
    control_operator = 4,
    error = 5
};

typedef struct  s_word
{
    char        *token;
    enum e_role role;
}               t_word;

void    destroy_word(t_word *word);
t_word  *create_word(char *input);
int     ft_strcmp(char *dst, char *src);
int     is_a_command(t_word *word);
#endif