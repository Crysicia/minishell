#include <criterion/criterion.h>
#include "../includes/header.h"

Test_lexer_fct(example_suite, example_test) {
    cr_expect(((lexer(NULL)) == -1), "Expect lexer to raise error if line is NULL");
}