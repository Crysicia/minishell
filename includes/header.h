/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/09 11:35:08 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <limits.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "scanner.h"

typedef struct s_command
{
	char	*executable;
	char	**args;
	char	**envp;
}				t_command;

void	print_prompt(void);
void	get_command(char *envp[]);
int		lexer(char *line, char *envp[]);
char	*get_word(char **line);
void	skip_spaces(char **line);
int		builtin_env(char *envp[]);

int		change_directory(t_list **env_list, char *new_path);
int		is_valid_path(char *path);
int		execute_command(char **command);
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
void	display_error(char *command, char *custom);
bool	is_env_valid(char *env, bool can_contain_eq);

int		(*get_builtin(char *str))(char **arguments);
int		builtin_cd(char **arguments);
int		builtin_echo(char **arguments);
int		builtin_env(char **arguments);
int		builtin_exit(char **arguments);
int		builtin_export(char **arguments);
int		builtin_pwd(char **arguments);
int		builtin_unset(char **arguments);
int		execute_builtin(char *str, char **arguments);

bool	is_path(char *path);
bool	is_absolute_path(char *path);

int		set_status_code(int code, bool from_builtin);
/* TMP UTILS */

void	print_token_list(t_list *list);
void	print_simple_command_node(t_simple_command *command);
void	print_pipeline(t_pipeline *pipeline);
void	print_command_list(t_list *list);
/* Error managment */
void	ft_malloc_error(void);
void	syntax_error(void);
void	parser_error(int ret);
int		test_redirections(void);

void	handle_redirections(t_list *command);
int		execute_single_command(t_simple_command *commands);


// int execute_basic_command(t_list **commands);
// int execute_commands(t_list **commands);
// int execute_single_command(t_list **commands, t_pipes *pipes);


#endif
