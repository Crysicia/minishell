/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:09:55 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/12 19:58:25 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*find_exe_path(char *command)
{
	struct stat	st;
	char		**path_arr;
	char		*current_path;
	char		*result;
	int			index;

	if (is_path(command))
	{
		if ((stat(command, &st) == 0) && (st.st_mode & S_IXUSR & S_IFREG))
			return (command);
		return (NULL);
	}
	index = -1;
	result = NULL;
	path_arr = list_exe_paths();
	while (path_arr && path_arr[++index] && !result)
	{
		current_path = get_full_path(path_arr[index], command);
		if ((stat(current_path, &st) == 0) && (st.st_mode & S_IXUSR))
			result = current_path;
		else
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
