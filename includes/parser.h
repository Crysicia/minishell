/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:09:25 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/10 17:04:17 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"
# include "token.h"

typedef enum e_command_type
{
	simple_command,
	pipeline
}				t_command_type;

typedef struct s_redirection
{
	struct s_token	*operator;
	struct s_token	*file;
}				t_redirection;

typedef struct s_simple_command
{
	t_command_type	type;
	struct s_list	*words;
	struct s_list	*redirections;
}				t_simple_command;

typedef struct s_pipeline
{
	t_command_type	type;
	int				pipe_count;
	struct s_list	*commands;
}				t_pipeline;

t_simple_command	*new_simple_command(void);
t_redirection		*new_redirection(void);
t_pipeline			*new_pipeline(t_simple_command *first);
bool				check_if_pipeline(t_simple_command *command);

t_list				*parser_loop(char *line);
t_simple_command	*parse_simple_command(char **line);
void				parse_redirection(char **line,
						t_simple_command *command,
						struct s_token *token);

#endif
