#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../includes/header.h"
#include "helpers.h"
#include <fcntl.h>


/*
**----------------------------------------------
**-
**-                 IS_PATH
**-
**----------------------------------------------
*/

typedef struct	s_is_path_params {
	bool ret;
	char argument[42];
}				t_is_path_params;

ParameterizedTestParameters(path_utils_suite, is_path_test) {
	static  t_is_path_params is_path_params[] = {
		{ .ret = true, .argument = "./test" },
		{ .ret = true, .argument = "/test" },
		{ .ret = true, .argument = "test/bonjour" },
		{ .ret = true, .argument = "../test" },
		{ .ret = true, .argument = "../test/../bonjour/test" },
		{ .ret = false, .argument = "" },
		{ .ret = false, .argument = "bonjour" },
		{ .ret = false, .argument = "te..st" },
		{ .ret = false, .argument = ".ls" },
	};

	return cr_make_param_array(t_is_path_params, is_path_params, sizeof(is_path_params) / sizeof(t_is_path_params));
}

ParameterizedTest(t_is_path_params *is_path_params, path_utils_suite, is_path_test) {
	char og_buffer[6];
	char ret_buffer[6];
	bool ret = is_path(is_path_params->argument);
	cr_expect(ret == is_path_params->ret, "Expected is_path to return [%s], instead got [%s], for [%s]",
		bool_to_str(og_buffer, is_path_params->ret),
		bool_to_str(ret_buffer, ret),
		is_path_params->argument
	);
}
