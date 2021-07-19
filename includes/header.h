/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/19 11:15:45 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
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
# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line.h"
# include "../libft/libft.h" 
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
	int		*pids;
	int		status;
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
void	run_minishell(void);
bool	destroy_globals(void);
bool	init_globals(char *envp[]);

void	handle_sigint(int signal);
void	handle_sigquit(int signal);

/* Parsing */

char	*get_command(void);
bool	is_space(int c);
bool	ft_is_blank(char *str);
char	*get_word(char **line);
void	skip_spaces(char **line);

/* Execution */

int		evaluation_pass(t_list *list);
bool	check_command_syntax(t_list *list);
int		execute_command(char **command);
int		execve_argument(char **arguments);
void	execute_all_the_commands(t_list *list);
size_t	count_command_words(t_list *list);
char	**command_format(t_list *list);

char	*find_exe_path(char *command);
char	**list_exe_paths(void);

/* Evaluate tokens */

int		flag_simple_command(t_simple_command *list);
int		flag_pipeline(t_pipeline *list);
int		copy_quoted_string(char quote, char *str, char *buffer);
void	copy_double_quoted_text(char **str, char **buffer);
int		count_expanded_len(char *str);
void	copying_loop(char **str, char *expanded);
char	*get_variable_name_and_add_len(char *str, int *i, int *len);

/* Variable expansion */

char	*get_variable_name(char **str);
void	expand_exit_status(char **str, char **buffer);

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

bool	is_builtin(char *str);
bool	is_env_valid(char *env, bool can_contain_eq);
bool	is_path(char *path);
int		is_valid_path(char *path);
bool	is_executable(char *path);
char	*get_executable_path(char *path);
bool	is_absolute_path(char *path);
char	*get_full_path(char *path, char *executable);
int		set_status_code(int code, bool from_builtin);

int		change_directory(t_list **env_list, char *new_path);
t_dict	*env_to_dict(char *env);
char	*dict_to_env(t_dict *dict);
t_dict	*ft_getenv(const char *name);
int		ft_setenv(char *name, char *value);
int		ft_unsetenv(char *name);
void	copy_env_var_to_buffer(char **str, char *buffer);

/* Redirections */

int		expand_redirection(t_redirection *redirection);
int		handle_redirections(t_list *command);
int		apply_all_redirections(t_list *command);
int		create_file(char *path, char *redirection_type);
void	apply_redirection(int fd, char *redirection_type);
void	load_heredoc(int fd, char *heredoc_end);
int		heredoc_routine(int fd, char *heredoc_end);
bool	save_in_and_out(int (*saved)[]);
bool	restore_in_and_out(int (*saved)[]);

int		close_all_fds(t_list *command);

/* Pipelines */

typedef struct s_pipe_holder
{
	t_list	*scmd_list;
	int		index;
	int		**pipe_tab;
	int		*pid_tab;
	int		in_and_out[2];
}				t_tmp_pipe;

int		execute_single_command(t_simple_command *commands);
int		execute_pipe_command(int pipe_fd[2], t_simple_command *commands);
int		**allocate_pipe_tab(int	nb);
void	deallocate_pipe_tab(int **tab, int nb);
int		pipeline_big_loop(t_pipeline *pipeline);
int		piping_loop(t_pipeline *pipeline);
int		wait_pipeline_end(int pipe_count, int *pid_tab);
void	pipe_child_process_exec(int pipe_fd[2], t_simple_command *commands,
			char **arguments);
void	pipe_parent_process_exec(int pipe_fd[2], int fork_ret);
t_tmp_pipe	*init_pipeline_utils(t_pipeline *pipeline);
void	clean_up_pipeline_utils(t_tmp_pipe *tmp, t_pipeline *pipeline);

/* Miscellaneous */

bool	check_bash_c_option(char *argv);
int		bash_c_option(char *argv);

t_list	*ft_lstnew_safe(void *content, void (*del)(void *));
t_list	*array_to_list(char **array);
char	**list_to_array(t_list *list);
t_dict	*new_dict(char *key, char *value);
void	free_dict(void *elem);
void	*dup_dict(void *dict_ptr);

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

#endif
