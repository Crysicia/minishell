/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:17:41 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/11 11:31:19 by pcharton         ###   ########.fr       */
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
	int		*pids;
	int		status;
	char	last_token[3];
	t_list	*env;
}			t_globals;

t_globals	*g_globals;

typedef struct s_dict
{
	char	*key;
	char	*value;
}				t_dict;

void	print_prompt(void);
void	run_minishell(void);
bool	init_globals(char *envp[]);
bool	destroy_globals(void);

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
int		execute_single_command(t_simple_command *commands);
int		execute_command(char **command);
int		execve_argument(char **arguments);
void	execute_all_the_commands(t_list *list);
size_t	count_command_words(t_list *list);
char	**command_format(t_list *list);
void	find_and_exec_command(char **arguments);

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

char	*expand_text(char *str);
char	*get_variable_name(char **str);
void	expand_exit_status(char **str, char **buffer);
void	add_a_dollar(char **buffer);
void	remove_quoting(char *str);

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
int		look_for_heredoc(t_list *list);
void	load_heredoc(int fd, char *heredoc_end);
int		heredoc_routine(int fd, char *heredoc_end);
bool	save_in_and_out(int (*saved)[]);
bool	restore_in_and_out(int (*saved)[]);

int		close_all_fds(t_list *command);

/* Pipelines */

typedef struct s_pipe_holder
{
	t_list	*scmd_list;
	int		save_stdin;
	int		index;
	int		**pipe_tab;
}				t_pipe;

int		**allocate_pipe_tab(int	nb);
void	deallocate_pipe_tab(int **tab, int nb, bool should_close);
int		wait_pipeline_end(int pipe_count);

t_pipe	*init_pipeline_utils(t_pipeline *pipeline);
void	*free_pipeline_utils(t_pipe *t, t_pipeline *pipeline);
void	clean_up_pipeline_utils(t_pipe *tmp, t_pipeline *pipeline);

int		the_pipe_come_again(t_pipeline *pipeline);
int		ft_do_pipe(t_simple_command *cmd, int stdin, int stdout, int to_close);
void	v2_pipe_child_process_exec(t_simple_command *cmd, char **arguments);
void	v2_pipe_parent_process_exec(int to_close);

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

bool	check_pipeline(t_pipeline *pipeline);
bool	check_first_node_cmd(t_simple_command *cmd);
bool	check_redirections(t_list *list);

int		test_redirections(void);
bool	check_syntax_error(t_list *list);

void	add_pid_to_global(int pid);
void	reset_pids_from_global(void);

#endif
