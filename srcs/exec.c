/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/18 17:09:35 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*get_full_path(char *path, char *executable)
{
	char	current_path[PATH_MAX];

	ft_strlcpy(current_path, path, ft_strlen(path) + 1);
	ft_strlcat(current_path, "/", PATH_MAX);
	ft_strlcat(current_path, executable, PATH_MAX);
	return (ft_strdup(current_path));
}

char	**list_exe_paths(void)
{
	t_dict		*path;
	char		**result;

	path = ft_getenv("PATH");
	if (!path || !path->value)
		return (NULL);
	result = ft_split(path->value, ':');
	if (!result)
		return (NULL);
	else
		return (result);
}

char	*find_exe_path(char *command)
{
	struct stat	st;
	char		**path_arr;
	char		*current_path;
	char		*result;
	int			index;

	if (is_path(command))
		return (command);
	index = 0;
	result = NULL;
	path_arr = list_exe_paths();
	while (path_arr[index])
	{
		current_path = get_full_path(path_arr[index], command);
		if ((stat(current_path, &st) == 0) && (st.st_mode & S_IXUSR))
			result = current_path;
		else
		{
			free(current_path);
			current_path = NULL;
		}
		index++;
	}
	ft_free_matrix((void **)path_arr, index);
	return (result);
}

int	set_status_code(int code, bool from_builtin)
{
	printf("ERRNO: %s\n", strerror(errno));
	if (from_builtin)
		return (g_globals->status = code);
	g_globals->status = WEXITSTATUS(code);
	return (g_globals->status);
}

int	execute_command(char **command)
{
	char	*path;

	printf("execute_command, %s:%d\n", __FILE__, __LINE__);
	if (is_builtin(command[0]))
		exit(execute_builtin(command[0], &command[1]));
	path = find_exe_path(command[0]);
	if (!path)
		return (-1);
	execve(path, command, list_to_array(g_globals->env));
	return (-2);
}

int execute_single_command(t_list **commands) //t_pipes *pipes)
{
	(void)commands;
	// char	**arguments;
	// int		pid;
	// t_block *uniona;
	// // int		command_flag;

	// // command_flag = NOT_IN_PIPELINE;
	// uniona = (*commands)->content;
	// arguments = command_format(commands);
	// if (!arguments)
	// 	display_error("malloc error", "could not allocate arguments array");
	// pid = fork();
	// if (pid < 0)
	// {
	// 	display_error("Error", "Could not fork child process");
	// }
	// else if (pid == 0)
	// {
	// 	printf("CHILD---------\n");
	// 	// dup_pipes(pipes, command_flag);
	// 	// close_pipes(pipes);
	// 	handle_redirections(uniona->kind.cmd);
	// 	execute_command(arguments);
	// }
	// else
	// {
	// 	printf("PARENT\n");
	// 	// close_relevant_pipes(pipes, command_flag);
	// 	g_globals->current_pid = pid;
	// 	wait(&g_globals->status);
	// 	set_status_code(g_globals->status, false);
	// 	g_globals->current_pid = 0;
	// }
	return (0);
}

int execute_single_command_wip(t_simple_command *commands) //t_pipes *pipes)
{
	char	**arguments;
	int		pid;
	t_list	words;
	// int		command_flag;

	// command_flag = NOT_IN_PIPELINE;
	words = *commands->words;
	arguments = command_format(&words);
	if (!arguments)
		display_error("malloc error", "could not allocate arguments array");
	pid = fork();
	if (pid < 0)
	{
		display_error("Error", "Could not fork child process");
	}
	else if (pid == 0)
	{
		printf("CHILD---------\n");
		// dup_pipes(pipes, command_flag);
		// close_pipes(pipes);
		handle_redirections(commands->redirections);
		execute_command(arguments);
	}
	else
	{
		printf("PARENT\n");
		// close_relevant_pipes(pipes, command_flag);
		g_globals->current_pid = pid;
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		g_globals->current_pid = 0;
	}
	return (0);
}

int execute_commands(t_list **commands)
{
	// t_pipes pipes;
	int ret;

	ret = SUCCESS;
	// if (!create_pipes(&pipes))
	// 	display_error("Broken pipe", NULL);
	// while (commands && *commands)
		ret = execute_single_command(commands); //&pipes);
	// close_pipes(&pipes);
	return (ret);
}
