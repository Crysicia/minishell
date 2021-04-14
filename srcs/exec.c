/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/14 12:00:00 by lpassera         ###   ########.fr       */
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

int	find_exe_path(t_command *command)
{
	struct stat	st;
	char		*path;
	char		**path_arr;
	char		*current_path;
	int			index;

	index = 0;
	path = getenv("PATH");
	if (!path)
		return (-1);
	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (-1);
	current_path = NULL;
	while (path_arr[index] && !command->executable)
	{
		free(current_path);
		current_path = get_full_path(path_arr[index], command->args[0]);
		if (stat(current_path, &st) == 0 && (st.st_mode & S_IXUSR))
			command->executable = current_path;
		index++;
	}
	if (!command->executable)
		return (-2);
	return (0);
}

int	execute_command(t_command *command)
{
	int	pid;

	if (find_exe_path(command))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		execve(command->executable, command->args, command->envp);
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
