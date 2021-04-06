#include <criterion/criterion.h>
#include "../includes/grammar.h"
#include <string.h>

Test(grammar_suite, is_a_command_suite)
{
    t_word echo;
    t_word env;
    t_word error;

    echo.token = strdup("echo");
    cr_expect((is_a_command(&echo) == 0) && (echo.role == command), "this test should return 0 and role be set to command");
    env.token = strdup("env");
    cr_expect((is_a_command(&env) == 0) && (env.role == command), "this test should return 0 and role be set to command");
    env.token = strdup("blablabla");
    cr_expect(is_a_command(&env) == 0, "this test should return -1, word is an error");

}