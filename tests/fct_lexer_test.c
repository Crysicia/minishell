#include <criterion/criterion.h>
#include "../includes/header.h"
#include <string.h>

Test(header_suite, header_test) {
    cr_assert((lexer(NULL, (char **){ NULL })) == -1);
}

/* Test get word */
/*
Test(get_word_suite, echo_test) {
    char *result;
    char *input;

    input = "echo";
    result = get_word(&input);
    cr_expect(strcmp(result, "echo") == 0, "Lexing echo bonjour did not return expected command");
    free(result);
}
*/