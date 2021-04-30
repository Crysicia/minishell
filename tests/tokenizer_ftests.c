#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <string.h>
#include <stdio.h>
#include "../includes/token.h"

/*

    This section tests tokenizer behaviour.
    Tokenizer should :
        - differentiate words and operator
        - collect the word content or operator symbol
    Tokenizer does not modify the evaluated array.
    It only copies a part of it and stick a label.

    Tokenizer receives an array cleaned of spaces or tabs.
    Array cannot be null, as it has been checked before (?)
*/
/*
static struct test_token
{
    char input[200];
    char expected[50]
    t_tok_type type;
}   token;

ParameterizedTestParameters(tokenizer_behaviour, simple_quote_test)
{
    static token user_case[] = {
    {input = ""},
    };
        return (cr_make_param_array(t_tok_input_test, tests,
								sizeof(tests)/sizeof(t_tok_input_test)));
}
*/

Test(tokenizer_loop_suite, testing_normal_command)
{
    char        buffer[] = "'ec'\"ho\" bonjour ;";
    char        *expected_token_str[] = { "'ec'\"ho\"", "bonjour", ";"};
    t_tok_type expected_token_type[] = { word, word, operator};
    int         nb_of_tokens = 3;
    size_t len  = strlen(buffer);

    t_token     *token;
    char        *tmp = buffer;
    for (int i = 0; i < nb_of_tokens; i++)
    {
        token = get_next_token(tmp);
        cr_expect_str_eq(expected_token_str[i], token->cmd,
            "Test get_next_token on given command\n"
            "Input : [%s], Expected : [%s], Got : [%s]\n",
            buffer, expected_token_str[i], token->cmd);
        cr_assert_eq(expected_token_type[i], token->role);
        tmp = strstr(buffer, token->cmd);
        tmp += strlen(token->cmd);
        if (tmp >= buffer + len)
            break;
    }
}