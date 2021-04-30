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


    // Testing only parsing with no quote removal
    t_token     *token[3];
    char        *tmp = buffer;
    for (int i = 0; i < nb_of_tokens; i++)
    {
        token[i] = get_next_token(tmp);
        cr_expect_str_eq(expected_token_str[i], token[i]->cmd,
            "Test get_next_token on given command\n"
            "Input : [%s], Expected : [%s], Got : [%s]\n",
            buffer, expected_token_str[i], token[i]->cmd);
        cr_assert_eq(expected_token_type[i], token[i]->role);
        tmp = strstr(buffer, token[i]->cmd);
        tmp += strlen(token[i]->cmd);
        if (tmp >= buffer + len)
            break;
    }
    // Testing with quote removal juste before execve action
    char        *expected_token_trimmed[] = { "echo", "bonjour", ";"};
    for (int j = 0; j < nb_of_tokens; j++)
    {
        cr_log_warn("hool");
        quotes_removal(token[j]);
        cr_assert_str_eq(token[j]->cmd, expected_token_trimmed[j]);
    }
}