/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:09:55 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/15 15:28:16 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*find_exe_path(char *command)
{
	char		**path_arr;
	char		*current_path;
	char		*result;
	int			index;

	if (is_path(command))
		return (get_executable_path(command));
	index = -1;
	result = NULL;
	path_arr = list_exe_paths();
	while (path_arr && path_arr[++index] && !result)
	{
		current_path = get_full_path(path_arr[index], command);
		result = get_executable_path(current_path);
		free(current_path);
	}
	ft_free_matrix((void **)path_arr, ft_matrix_size((void **)path_arr));
	return (result);
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

char	*get_executable_path(char *path)
{
	if (is_executable(path))
		return (ft_strdup(path));
	return (NULL);
}

bool	is_executable(char *path)
{
	struct stat	st;

	if ((stat(path, &st) == 0) && (st.st_mode & S_IXUSR)
		&& (S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)))
		return (true);
	return (false);
}

// TODO: remove this function as it is unused
bool	is_absolute_path(char *path)
{
	if (!path)
		return (false);
	return (*path == '/');
}

bool	is_path(char *path)
{
	if (!path)
		return (false);
	return (!!ft_strchr(path, '/'));
}

char	*get_full_path(char *path, char *executable)
{
	char	current_path[PATH_MAX];

	ft_strlcpy(current_path, path, ft_strlen(path) + 1);
	ft_strlcat(current_path, "/", PATH_MAX);
	ft_strlcat(current_path, executable, PATH_MAX);
	return (ft_strdup(current_path));
}
