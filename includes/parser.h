/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:09:25 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/19 15:24:09 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"
# include "token.h"

typedef enum e_command_type
{
	simple_command,
	pipeline,
	only_redirections,
	error
}				t_command_type;

typedef struct s_redirection
{
	struct s_token	*operator;
	struct s_token	*file;
}				t_redirection;

typedef struct s_simple_command
{
	struct s_list	*words;
	struct s_list	*redirections;
}				t_simple_command;

typedef struct s_pipeline
{
	int				pipe_count;
	struct s_list	*commands;
}				t_pipeline;

typedef union u_kind
{
	struct s_simple_command	*cmd;
	struct s_pipeline		*pipe;
}			t_kind;

typedef struct s_block
{
	t_command_type	id;
	t_kind			kind;
}				t_block;

t_block				*new_block(void);
void				set_block_ptr(t_block *block, void *ptr);
void				free_block(void *to_free);

t_simple_command	*new_simple_command(void);
void				free_simple_command(void *to_free);

t_pipeline			*new_pipeline(t_simple_command *first);
void				free_pipeline(void *to_free);
bool				check_if_pipeline(t_simple_command *command);

t_redirection		*new_redirection(void);
void				free_redirection(void *to_free);


t_command_type		attribute_command_type(t_simple_command *command);

t_list				*parser_loop(char *line);
int					parse_simple_command(t_block *dst, char **line);
void				parse_redirection(char **line,
						t_simple_command *command,
						struct s_token *token);
int					parse_pipeline_command(t_block *first, char **line);

#endif
