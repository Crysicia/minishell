/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/06 12:42:09 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "scanner.h"

typedef struct s_command
{
	char	*executable;
	char	**args;
	char	**envp;
}				t_command;

void	print_prompt(void);
void	get_command(void);
int		lexer(char *line);
char	*get_word(char **line);
void	skip_spaces(char **line);
int		builtin_env(char *envp[]);

#endif
