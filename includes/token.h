/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:03:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/26 10:15:35 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "header.h"
# include "flag.h"

typedef enum e_tok_type
{
	word,
	operator
}				t_tok_type;

typedef struct s_token
{
	char			*cmd;
	int				flag;
	t_tok_type		role;
}					t_token;

t_list		*command_parse(char *line);
int			evaluate_token(t_list **list);
t_tok_type	get_next_tok_type(char *str);
t_tok_type	attribute_tok_type(char chr);
t_token		*get_next_token(char *line);
t_token		*get_next_token_rework(char **line);

void		free_token(void *token);
t_token		*new_token(char *str, t_tok_type type);

bool		is_valid_token(t_token tok);
bool		is_operator(char *str);
bool		is_redirection(char *str);
bool		is_escape_character(char chr);

char		*get_escaped_string(char *str);
int			get_word_size(char *line);
char		*cut_token_string(char *line);
void		quotes_removal(t_token *tok);
void		remove_simple_and_double_quotes(char *buffer, char *str);

void		word_flagger(t_token *token);
void		expand_env_variable(char **str, char **buffer);
void		dollar_expansion(t_token *tok);
void		copy_escaped_character(char **str, char **buffer);

#endif
