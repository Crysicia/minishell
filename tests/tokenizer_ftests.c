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

static struct test_token
{
    char input[200];
    char expected[50]
    t_tok_type type;
}   token;

Test