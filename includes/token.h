/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:03:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/15 12:09:06 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "../libft/libft.h"
#include "header.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum	e_tok_type
{
	tok_end_of_cmd = 0,
	tok_pipe = 1,
	tok_redir_l = 2,
	tok_append_r = 3,
	tok_redir_r = 4,
	tok_command = 5
}				t_tok_type;

typedef struct		s_token
{
	char			*cmd;
	t_tok_type		role;
}					t_token;

t_tok_type	get_next_tok_type(char *str);
t_list		*command_parse(char *line);
t_tok_type	attribute_tok_type(char chr);
t_token		*get_next_token(char *line);
void		free_token(void *token);
t_token		*new_token(char *str, t_tok_type type);

bool		is_escape_character(char chr);
bool		is_token_character(char chr);
char		*cut_token_string(char *line);

#endif
