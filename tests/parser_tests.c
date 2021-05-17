#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/header.h"

Test(parsing_suite, parsing_simple_cmd_test_1)
{
	char	*line = "ls -laaaa file;";

	t_list	*result;
	t_block	*try;
	result = parser_loop(line);
	try = result->content;
	cr_expect_eq(try->id, simple_command);


}