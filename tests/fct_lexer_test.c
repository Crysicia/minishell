#include <criterion/criterion.h>
#include "../includes/header.h"
#include <string.h>

Test(header_suite, header_test) {
    cr_assert((lexer(NULL)) == -1);
}

/* Test get word */

Test(get_word_suite, echo_bonjour_test) {
    char *result;
    char *input;
    char *save;

    input = "echo bonjour";
    save = input;
    result = get_word(&input);
    cr_expect(strcmp(result, "echo") == 0, "Lexing echo bonjour did not return expected command");
    free(result);
    result = get_word(&input);
    cr_expect(strcmp(result, "bonjour") == 0, "Lexing echo bonjour did not return expected argument")
    (void)save;
}