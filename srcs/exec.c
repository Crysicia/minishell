/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:13:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/07 18:16:11 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*get_full_path(char *path, char *executable)
{
	char	current_path[PATH_MAX];

	ft_bzero(current_path, PATH_MAX);
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

	path = getenv("PATH");
	if (!path)
		return (-1);
	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (-1);
	current_path = NULL;
	while (*path_arr && !command->executable)
	{
		free(current_path);
		current_path = get_full_path(*path_arr, command->args[0]);
		stat(current_path, &st);
		if (st.st_mode & S_IXUSR)
			command->executable = current_path;
		path_arr++;
	}
	return (0);
}

int	execute_command(t_command *command)
{
	find_exe_path(command);
	return (execve(command->executable, command->args, command->envp));
}
