/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:21:45 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/17 15:21:45 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef	struct	s_cd_env
{
	char	*pwd;
	char	*oldpwd;
	char	*home;
}				t_cd_env;

t_cd_env	*construct_cd_struct(char *pos)
{
	t_cd_env	*new;

	new = malloc(sizeof(t_cd_env));
	if (new)
	{
		new->pwd = pos;
		new->oldpwd = strdup("");
		new->home = getenv("HOME");
	}
	return (new);
}

void	destroy_cd_struct(t_cd_env *cd_struct)
{
	free(cd_struct->pwd);
	free(cd_struct->oldpwd);
	free(cd_struct->home);
	free(cd_struct);
}

void	update_pwd(t_cd_env *toto, char *new_path)
{
	free(toto->oldpwd);
	toto->oldpwd = toto->pwd;
	toto->pwd = new_path;
	//could need str allocation
}

void	update_home_manually(t_cd_env *cd_struc, char *home)
{
	//should it be freed ?
	//free(cd_struc->home);
	cd_struc->home = home;
}

char	*get_current_path(void)
{
	char	*current_path;

	current_path = getcwd(NULL, PATH_MAX);
	return (current_path);
}

/*
**	handle . .. 
**	~ behaviour needs to get home location
**	could code - behaviour
*/

void	go_to_parent_directory(t_cd_env *cd_struct)
{
	char	*tmp;
	char	*previous_path;

	tmp = strrchr(cd_struct->pwd, '/');
	if (tmp)
	{
		previous_path = strndup(cd_struct->pwd, tmp - cd_struct->pwd);
		chdir(previous_path);
		update_pwd(cd_struct, previous_path);
	}
}

void	go_to_input_path(t_cd_env *cd_struct, char *path)
{
	int	res;

	res = chdir(path);
	if (res)
	{
		char *error = strerror(errno);
		//could prolly generalize this error msg with a wrapper
		printf("Minishell: cd: %s: %s\n", path, error);
	}
	else
	{
		return ;
	}

}

void main(void)
{
	char		*current_path;
	t_cd_env	*cd;

	current_path = get_current_path();
	cd = construct_cd_struct(current_path);
	go_to_parent_directory(cd);
	go_to_input_path(cd, "zjbvz");
}