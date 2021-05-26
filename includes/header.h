/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:30:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <string.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include "scanner.h"
# include "token.h"
# include "parser.h"
# include "pipes.h"
# include "flag.h"
# define BUILTINS_NB 7

/* ERRORS */
# define SUCCESS 0
# define ERR_BUILTIN_FAILED 1
# define ERR_UNEXPECTED_TOKEN 12
# define ERR_MALLOC_FAILED 256
# define ERR_ENV_NOT_FOUND 257
# define ERR_COULD_NOT_SET_ENV 258
# define ERR_PIPE_FAILED 259
# define ERR_FORK_FAILED 260

# define MSG_MALLOC_FAILED "Malloc has failed during program run. Exiting now."

typedef struct s_globals
{
	int		current_pid;
	int		status;
	t_list	*current_cmd;
	t_list	*env;
	t_dlist	*history;
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

/* Minishell working */
void	print_prompt(void);
void	handle_sigint(int signal);

int		evaluation_pass(t_list *list);
bool	check_command_syntax(t_list *list);
void	execute_all_the_commands(t_list *list);
void	run_minishell(void);

size_t	count_command_words(t_list *list);
char	**command_format(t_list *list);
char	*get_command(void);

char	*get_word(char **line);
void	skip_spaces(char **line);

int		change_directory(t_list **env_list, char *new_path);
int		is_valid_path(char *path);
int		execute_command(char **command);
int		execve_argument(char **arguments);

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

/* Evaluate tokens */
int		flag_simple_command(t_simple_command *list);

void	remove_simple_and_double_quotes(char *buffer, char *str);
int		copy_quoted_string(char quote, char *str, char *buffer);

/* Builtins */

int		(*get_builtin(char *str))(char **arguments);
int		builtin_cd(char **arguments);
int		builtin_echo(char **arguments);
int		builtin_env(char **arguments);
int		builtin_exit(char **arguments);
int		builtin_export(char **arguments);
int		builtin_pwd(char **arguments);
int		builtin_unset(char **arguments);
int		execute_builtin(char *str, char **arguments);

bool	is_env_valid(char *env, bool can_contain_eq);
bool	is_path(char *path);
bool	is_absolute_path(char *path);
char	*get_full_path(char *path, char *executable);
int		set_status_code(int code, bool from_builtin);

/* History utils */

int		add_to_history(char *line);

/* Miscellaneous */

bool	check_bash_c_option(char *argv);
int		bash_c_option(char *argv);
void	do_parent_process_stuff(int pid);

void	ft_exit_with_error_msg(char *msg);
void	ft_exit(void);

/* Debug utils */

void	print_simple_command_node(t_simple_command *command);
void	print_pipeline(t_pipeline *pipeline);
void	print_command_list(t_list *list);
void	print_command_history(t_dlist *history);

/* Error managment */

void	display_error(char *command, char *custom);
void	ft_malloc_error(void);
void	syntax_error(void);
int		test_redirections(void);
bool	check_syntax_error(t_list *list);

void	handle_redirections(t_list *command);
int		execute_single_command(t_simple_command *commands);
bool	save_in_and_out(int (*saved)[]);
bool	restore_in_and_out(int (*saved)[]);

// int execute_basic_command(t_list **commands);
// int execute_commands(t_list **commands);
// int execute_single_command(t_list **commands, t_pipes *pipes);

#endif
