#include <criterion/criterion.h>
#include <criterion/parameterized.h>
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

typedef struct	s_cd_testing
{
	char path[42];
	char expected_oldpwd[42];
	char expected_pwd[42];
}				t_cd_testing;

// Need to improve this test.

ParameterizedTestParameters(cd_builtin, valid_path_tests)
{
	static t_cd_testing test[] =
	{
		{.path = "", .expected_oldpwd = "/toto", .expected_pwd = "/root"},
		{.path = ".", .expected_oldpwd = "/toto", .expected_pwd = "/toto"},
		{.path = "../", .expected_oldpwd = "/toto", .expected_pwd = "/"},
		{.path = "./", .expected_oldpwd = "/toto", .expected_pwd = "/toto"},
		{.path = ".. ewighqiuvh", .expected_oldpwd = "/toto", .expected_pwd = "/"},
		{.path = "/etc", .expected_oldpwd = "/toto", .expected_pwd = "/etc"},
		{.path = "totally_invalid_path", .expected_oldpwd = "OLDPWD=/Users/Pedro/Tests", .expected_pwd = "/toto"},
	};
	return cr_make_param_array(t_cd_testing, test, sizeof(test)/sizeof(t_cd_testing));
}

ParameterizedTest(t_cd_testing *params, cd_builtin, valid_path_tests)
{
	char *test_var[] = {"HOME=/root","LANG=fr","NAME=pierre","OLDPWD=/Users/Pedro/Tests","PWD=/toto"};
	t_list	*env = array_to_list(test_var);
	t_dict *oldpwd = find_var(&env, "OLDPWD");
	t_dict *pwd = find_var(&env, "PWD");

	int	res = 0;
	res = change_directory(&env, params->path);
	
	cr_assert_null(res);
	cr_assert_str_eq(oldpwd->value, params->expected_oldpwd);
	cr_assert_str_eq(pwd->value, params->expected_pwd);
}

//Some unit testings

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