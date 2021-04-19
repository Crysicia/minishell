/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/19 11:48:52 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <limits.h>
# include <signal.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include "scanner.h"
# include "token.h"
# define BUILTINS_NB 7

typedef struct s_globals
{
	int		current_pid;
	t_list	*env;
}			t_globals;

t_globals	*g_globals;

typedef struct s_command
{
	char	*executable;
	char	**args;
	char	**envp;
}				t_command;

typedef struct s_dict
{
	char	*key;
	char	*value;
}				t_dict;

void	print_prompt(void);
void	get_command(char *envp[]);
int		lexer(char *line, char *envp[]);
char	*get_word(char **line);
void	skip_spaces(char **line);
int		builtin_env(t_command *command);

int		execute_command(t_command *command);
int		find_exe_path(t_command *command);
bool	is_builtin(char *str);

t_list	*array_to_list(char **array);
char	**list_to_array(t_list *list);
t_dict	*ft_getenv(const char *name);
bool	destroy_globals(void);
bool	init_globals(char *envp[]);
t_dict	*new_dict(char *key, char *value);
t_dict	*env_to_dict(char *env);
char	*dict_to_env(t_dict *dict);
int		ft_setenv(char *name, char *value);
void	free_dict(void *elem);
#endif
