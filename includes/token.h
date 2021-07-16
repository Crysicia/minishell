/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:03:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/16 11:46:14 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "header.h"
# include "flag.h"

typedef enum e_tok_type
{
	operator,
	redirection,
	word
}				t_tok_type;

typedef struct s_token
{
	char			*cmd;
	int				flag;
	t_tok_type		role;
}					t_token;

t_list		*command_parse(char *line);
int			evaluate_token(t_list **list);
t_token		*get_next_token(char **line);

t_token		*new_token(char *str, t_tok_type type);
void		free_token(void *token);
bool		is_operator(char *str);
bool		is_redirection(char *str);
bool		is_escape_character(char chr);
t_tok_type	get_token_role(char *line);

char		*cut_token_string(char *line);
int			get_word_size(char *line);
int			add_quote_len(char quote, char *str);
bool		is_quote_closed(char quote, char *str);

void		word_flagger(t_token *token);

void		expand_env_variable(char **str, char **buffer);
void		copy_escaped_character(char **str, char **buffer);

int			parser_error(t_token *tok);

int			remove_mixed_quotes(t_token *token);
char		*expand_text(char *str);
void		copy_unquoted_text(char **str, char **buffer);
void		copy_simple_quoted_text(char **str, char **buffer);
void		copy_double_quoted_text(char **str, char **buffer);

#endif
