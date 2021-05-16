#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/header.h"

Test(parsing_suite, parsing_simple_cmd_test_1)
{
	char	line[50] = "ls -laaaa file;";

	t_block	*result;

	result = parser_loop(&line);
	cr_expect_eq(result->id, simple_command);
	

}