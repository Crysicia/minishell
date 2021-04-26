#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>

#define TEST_PATH_LEN 200

typedef struct	s_builtin_pwd_params {
	int ret;
	char path[TEST_PATH_LEN];
	char expected[TEST_PATH_LEN];
}				t_builtin_pwd_params;

ParameterizedTestParameters(exec_builtin_suite, builtin_pwd_test) {
	static  t_builtin_pwd_params builtin_pwd_params[] = {
		{ .ret = 0, .path = "/", .expected = "/\n" },
		{ .ret = 0, .path = "/usr", .expected = "/usr\n" },
		{ .ret = 0, .path = "/bin", .expected = "/bin\n" },
		{ .ret = 0, .path = "/home", .expected = "/home\n" },
	};

	return cr_make_param_array(t_builtin_pwd_params, builtin_pwd_params, sizeof(builtin_pwd_params) / sizeof(t_builtin_pwd_params));
}

ParameterizedTest(t_builtin_pwd_params *builtin_pwd_params, exec_builtin_suite, builtin_pwd_test) {
	char buffer[TEST_PATH_LEN + 4];
	int ret;
	FILE *fp = NULL;
	int fd = 0;

	chdir(builtin_pwd_params->path);

	fp = freopen("pwd.test", "w", stdout);
	ret = builtin_pwd(NULL);
	fclose(fp);

	fd = open("pwd.test", O_RDONLY);
	int rd = read(fd, buffer, TEST_PATH_LEN);
	buffer[rd] = 0;
	close(fd);

	cr_expect_eq(ret, builtin_pwd_params->ret, "Expected builtin_pwd to return [%d], instead got [%d]", builtin_pwd_params->ret, ret);
	cr_expect_str_eq(buffer, builtin_pwd_params->expected, "Expected builtin_pwd to print [%s], instead got [%s]", builtin_pwd_params->expected, buffer);
}
