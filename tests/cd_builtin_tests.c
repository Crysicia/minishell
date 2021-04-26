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
	int res = builtin_cd(NULL);
	cr_assert_eq(res, -1);
}

char *valid_path[] = {"", ".", "../", "./", ".. weviuwviu", "/etc" };
int	tests_nb = 6;

typedef struct	s_cd_testing
{
	char path[42];
	char expected_oldpwd[42];
	char expected_pwd[42];
	int	res;
}				t_cd_testing;

// Need to improve this test.
void init_filesystem(void)
{
	system("mkdir -p /parent/child/");
	chdir("/parent");
	system("touch /parent/test");
}

void	destroy_filesystem(void)
{
	system("rm -rf /parent");
}

ParameterizedTestParameters(cd_builtin, valid_path_tests)
{
	static t_cd_testing test[] =
	{
		{.path = "", .expected_oldpwd = "/parent", .expected_pwd = "/root", .res = 0},
		{.path = ".", .expected_oldpwd = "/parent", .expected_pwd = "/parent", .res = 0},
		{.path = "../", .expected_oldpwd = "/parent", .expected_pwd = "/", .res = 0},
		{.path = "./", .expected_oldpwd = "/parent", .expected_pwd = "/parent", .res = 0},
		{.path = "./child", .expected_oldpwd = "/parent", .expected_pwd = "/parent/child", .res = 0},
		{.path = ".. ewighqiuvh", .expected_oldpwd = "/parent", .expected_pwd = "/", .res = 0},
		{.path = "/etc", .expected_oldpwd = "/parent", .expected_pwd = "/etc", .res = 0},
		{.path = "totally_invalid_path", .expected_oldpwd = "OLDPWD=/Users/Pedro/Tests", .expected_pwd = "/parent", .res = -1},
	};
	return cr_make_param_array(t_cd_testing, test, sizeof(test)/sizeof(t_cd_testing));
}

ParameterizedTest(t_cd_testing *params, cd_builtin, valid_path_tests, .init=init_filesystem, .fini=destroy_filesystem)
{
	char *test_var[] = {"HOME=/root","LANG=fr","NAME=pierre","OLDPWD=/Users/Pedro/Tests","PWD=/toto"};
	init_globals(test_var);
	t_dict *oldpwd = find_var(&g_globals->env, "OLDPWD");
	t_dict *pwd = find_var(&g_globals->env, "PWD");

	int	res = 0;
	res = builtin_cd(params->path);
	
	cr_assert_eq(res, params->res);
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