/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/23 15:36:59 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include <sys/wait.h>

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
	return (result);
}

int	execute_command(char **command, char *envp[])
{
	int		pid;
	char	*path;

	if (is_builtin(command[0]))
		return (execute_builtin(command[0], &command[1]));
	path = find_exe_path(command[0]);
	if (!path)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		execve(path, command, envp);
		exit(0);
	}
	else if (pid > 0)
	{
		g_globals->current_pid = pid;
		wait(NULL);
		g_globals->current_pid = 0;
	}
	else
		printf("ERROR: Could not create child process.\n");
	return (0);
}
