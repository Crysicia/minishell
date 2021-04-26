/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/26 14:26:02 by lpassera         ###   ########.fr       */
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
	int		status_code;
	t_list	*env;
	char	**envp_tmp;
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
t_list	*parse_to_list(char *line);
char	**command_format(t_list **list);
char	*get_command(void);

char	*get_word(char **line);
void	skip_spaces(char **line);

int		change_directory(t_list **env_list, char *new_path);
int		is_valid_path(char *path);
int		execute_command(char **command, char *envp[]);
char	*find_exe_path(char *command);
bool	is_builtin(char *str);

t_list	*ft_lstnew_safe(void *content, void (*del)(void *));
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
void	*dup_dict(void *dict_ptr);
int		ft_unsetenv(char *name);

/* Builtins */

int		(*get_builtin(char *str))(char **arguments);
int		builtin_cd(char *new_path);
int		builtin_pwd(char **arguments);
int		builtin_export(char **arguments);
int		builtin_env(char **arguments);
int		execute_builtin(char *str, char **arguments);

bool	is_path(char *path);
bool	is_absolute_path(char *path);

/* TMP UTILS */
void	print_token_list(t_list *list);

/* Error managment */
void	ft_malloc_error(void);
void	syntax_error(void);
#endif
