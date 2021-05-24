/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/24 12:33:52 by lpassera         ###   ########.fr       */
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
	if (from_builtin)
		return (g_globals->status = code);
	g_globals->status = WEXITSTATUS(code);
	return (g_globals->status);
}

int	execute_command(char **command)
{
	int		pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		display_error("Error", "Could not fork child process");
	else if (pid == 0)
	{
		path = find_exe_path(command[0]);
		if (!path)
			return (-1);
		execve(path, command, list_to_array(g_globals->env));
	}
	else
	{
		g_globals->current_pid = pid;
		wait(&g_globals->status);
		set_status_code(g_globals->status, false);
		g_globals->current_pid = 0;
	}
	return (-2);
}

// TODO: Fd error management
int	execute_single_command(t_simple_command *commands)
{
	char	**arguments;
	t_list	words;
	int		in_and_out[2];

	words = *commands->words;
	arguments = command_format(&words);
	if (!arguments)
		display_error("malloc error", "could not allocate arguments array");
	save_in_and_out(&in_and_out);
	handle_redirections(commands->redirections);
	if (is_builtin(arguments[0]))
		set_status_code(execute_builtin(arguments[0], &arguments[1]), true);
	else
		execute_command(arguments);
	restore_in_and_out(&in_and_out);
	return (0);
}
