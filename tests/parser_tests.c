#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/header.h"

Test(parsing_suite, parsing_simple_cmd_test_1)
{
	char	*line = "ls -laaaa file;";

	t_list	*result;
	result = parser_loop(line);
	cr_assert(result);

	t_block	*try;
	try = result->content;
	cr_expect_eq(try->id, simple_command);
}

Test(parsing_suite, parsing_pipeline_test_1)
{
	char	*line = "ls | wc;";

	t_list	*result;
	result = parser_loop(line);
	cr_assert(result);

	t_block	*try;
	try = result->content;
	cr_expect_eq(try->id, pipeline);
}

Test(parsing_suite, parsing_only_redirection_test)
{
	char	*line = ">> file";

	t_list	*result;
	result = parser_loop(line);
	cr_assert(result);

	t_block	*try;
	try = result->content;
	cr_expect_eq(try->id, only_redirections);
}
