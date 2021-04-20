#include <criterion/criterion.h>
#include "../includes/header.h"
// CD CMD TEST
/*
**	Update OLDPWD AND PWD
**	save HOME
**	use case :
**	cd .
**	cd ..
**	cd - (not yet)
*/

// For cd we need to check that
// new_path is valid
// cd only takes the first argument and dumps the other
int		change_directory(t_list **env_list, char *new_path)
{
	if (!new_path)
		return (-1);
	(void)*env_list;
	(void)new_path;
	return (0);
}

int		is_valid_path(char *path)
{
	(void)path;
	return 42;
}

t_dict *find_var(t_list **env, char *var)
{
	t_dict	*dico;
	t_list	*list;

	list = *env;
	while (list)
	{
		dico = list->content;
		if (!strcmp(var, dico->key))
			return (dico);
		else
			list = list->next;
	}
	return (NULL);
}

Test(cd_builtin, new_path_null)
{
	t_list *empty = NULL;
	int res = change_directory(&empty, NULL);
	cr_assert_eq(res, -1);
}

char *valid_path[] = {"", ".", "../", "./", ".. weviuwviu", "/etc" };
int	tests_nb = 6;

Test(cd_builtin, change_directory_tests)
{
	char *test_var[] = {"HOME=/root","LANG=fr","NAME=pierre","OLDPWD=/Users/Pedro/Tests","PWD=/toto",
					"PATH=/bonjour/haha", "USER=pchartonesque","WSLENV=PAF"};
	char *expected_oldpwd[] = {"/toto", "/toto", "/toto", "/toto", "/toto", "/toto" };
	char *expected_pwd[] = {"/root", "/toto", "/", "", "/toto", "/", "/etc" };

	int	res = 0;
	t_list	*env = array_to_list(test_var);
	t_dict *oldpwd = find_var(&env, "OLDPWD");
	t_dict *pwd = find_var(&env, "PWD");

	for (int i = 0; i < tests_nb; i++)
	{
		res = change_directory(&env, valid_path[i]);
		//expect Old pwd and pwd to change		
		cr_assert_null(res);
		cr_assert_str_eq(oldpwd->value, expected_oldpwd[i]);
		cr_assert_str_eq(pwd->value, expected_pwd[i] );
	}
}

Test(cd_builtin, is_valid_path_wrong)
{
	int	res = is_valid_path("akghiugehg");
	cr_expect_eq(res, -1);
}

Test(cd_builtin, is_valid_path_right)
{
	char *ptr = getenv("HOME");
	int res = is_valid_path(ptr);
	cr_expect_null(res, "res should return 0 if path is valid");
	cr_free(ptr);

	for (int i = 0; i < tests_nb; i++)
	{
		int res = is_valid_path(valid_path[i]);
		cr_expect_null(res, "res should return 0 if path is valid");
	}
}