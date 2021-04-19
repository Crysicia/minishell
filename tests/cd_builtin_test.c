#include <criterion.h>

// CD CMD TEST
/*
**	Update OLDPWD AND PWD
**	save HOME
**	use case :
**	cd .
**	cd ..
**	cd -
*/

char	*get_home_var(t_list **env_list);
int		update_env_var(t_list **env_list, char *var);
int		change_directory(t_list **env_list, char *new_path);

char *test_var[] = {"HOME","HOSTTYPE","LANG","LESSCLOSE","LESSOPEN","LOGNAME",
			"LS_COLORS","MOTD_SHOWN","NAME","OLDPWD","PATH","PWD","SHELL","SHLVL","TERM",
					"USER","WSLENV","WSL_DISTRO_NAME","WSL_INTEROP","XDG_DATA_DIRS"}

t_list *test_list;

void	init_cd_tests(char *envp)
{
	char	*ptr;
	char	**array;
	int i = 0;
	int count = 0;

	while (test_var([i])
	{
		ptr = get_env(test_var[i]);
		if (ptr)
			count++;
		i++;
	}

	array = malloc(sizeof(char **) * (count + 1));

	i = 0;
	count = 0;
		while (test_var([i])
	{
		ptr = get_env(test_var[i]);
		if (ptr)
			array[count++] = strdup(ptr);
		i++;
	}

	g_globals->env = array_to_list(array);

	i = 0;
	while (i < count)
	{
		cr_free(array[i]);
		i++;
	}
	
	cr_free(array);
}

Test(cd_builtin, get_home_var_fct)
{
	t_dict	home;
	home->key = strdup("HOME");
	home->value = strdup("/bonjour/example");

	t_list	test;
	test->content = &home;
	test->next = NULL;

	//normal behaviour
	cr_assert_str_eq(get_home_var(&test), home->value);

	cr_free(home->key);
	home->key = strdup("HOMIE");
	test->content = &home;
}

Test(cd_builtin, get_home_var_null_test)
{
	t_list *env = NULL;
	cr_assert_null(get_home_var(&test));
}

Test(cd_builtin, update_env_var_fct)
{
	cr_assert_eq(update_env_var())
}

Test(cd_builtin, change_directory)
{	
}

