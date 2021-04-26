#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include <string.h>
#include <errno.h>
// CD CMD TEST
/*
**	Update OLDPWD AND PWD
**	save HOME
**	use case :
**	cd .
**	cd ..
**	cd - (not yet)
*/

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
	struct stat st = {0};

	if (stat("/parent", &st) == -1) {
	    mkdir("/parent", 0700);
	}
	if (stat("/parent/child", &st) == -1) {
	    mkdir("/parent/child", 0700);
	}
	chdir("/parent");
	open("/parent/test", O_CREAT);
}

void	destroy_filesystem(void)
{
	system("rm -rf /parent");
}

ParameterizedTestParameters(cd_builtin, valid_path_tests)
{
	static t_cd_testing test[] =
	{
		{.path = "", .expected_oldpwd = "/parent", .expected_pwd = "/parent", .res = 0},
		{.path = ".", .expected_oldpwd = "/parent", .expected_pwd = "/parent", .res = 0},
		{.path = "../", .expected_oldpwd = "/parent", .expected_pwd = "/", .res = 0},
		{.path = "./", .expected_oldpwd = "/parent", .expected_pwd = "/parent", .res = 0},
		{.path = "./child", .expected_oldpwd = "/parent", .expected_pwd = "/parent/child", .res = 0},
		{.path = "/etc", .expected_oldpwd = "/parent", .expected_pwd = "/etc", .res = 0},
		{.path = "totally_invalid_path", .expected_oldpwd = "", .expected_pwd = "/parent", .res = 1},
	};
	return cr_make_param_array(t_cd_testing, test, sizeof(test)/sizeof(t_cd_testing));
}

ParameterizedTest(t_cd_testing *params, cd_builtin, valid_path_tests, .init=init_filesystem, .fini=destroy_filesystem)
{
	char *test_var[] = {"HOME=/root","LANG=fr","NAME=pierre","OLDPWD=","PWD=/parent"};
	init_globals(test_var);
	t_dict *oldpwd = ft_getenv("OLDPWD");
	t_dict *pwd = ft_getenv("PWD");
	char *args[2];
	char *cwd;

	args[0] = params->path;
	args[1] = NULL;
	int	res = 0;

	res = builtin_cd(args);
	cwd = getcwd(NULL, 0);

	cr_expect_eq(res, params->res);
	cr_expect_str_eq(oldpwd->value, params->expected_oldpwd);
	cr_expect_str_eq(pwd->value, params->expected_pwd);
	cr_expect_str_eq(cwd, params->expected_pwd, 
		"Expected current working directory to be [%s], instead got [%s], for path [%s]",
		params->expected_pwd,
		cwd,
		params->path
	);
}

Test(cd_builtin, valid_path_mult_args_tests, .init=init_filesystem, .fini=destroy_filesystem)
{
	char *test_var[] = {"HOME=/root","LANG=fr","NAME=pierre","OLDPWD=","PWD=/parent"};
	init_globals(test_var);
	t_dict *oldpwd = ft_getenv("OLDPWD");
	t_dict *pwd = ft_getenv("PWD");
	char *args[3] = { "..", "ewighqiuvh", NULL };
	char *cwd;

	int	res = 0;
	res = builtin_cd(args);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cr_log_warn("Error with getcwd, errno is %d %s", errno, strerror(errno));
	cr_expect_eq(res, 0);
	cr_expect_str_eq(oldpwd->value, "/parent");
	cr_expect_str_eq(pwd->value, "/");
	cr_expect_str_eq(cwd, "/", 
		"Expected current working directory to be [%s], instead got [%s], for path [%s]",
		"/",
		cwd,
		".. ewighqiuvh"
	);
}

Test(cd_builtin, new_path_null)
{
	char *test_var[] = {"HOME=/root","LANG=fr","NAME=pierre","OLDPWD=","PWD=/parent"};
	init_globals(test_var);
	t_dict *oldpwd = ft_getenv("OLDPWD");
	t_dict *pwd = ft_getenv("PWD");
	char *cwd;
	int	res = 0;
	res = builtin_cd(NULL);
	cwd = getcwd(NULL, 0);

	cr_expect_eq(res, 0);
	cr_expect_str_eq(oldpwd->value, "/parent");
	cr_expect_str_eq(pwd->value, "/root");
	cr_expect_str_eq(cwd, "/root", 
		"Expected current working directory to be [%s], instead got [%s], for path [%s]",
		"/root",
		cwd,
		""
	);
}
