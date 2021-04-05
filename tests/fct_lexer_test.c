#include <criterion/criterion.h>
#include "../includes/header.h"

Test_lexer_fct(header_suite, header_name) {
    cr_expect((, "Expect lexer to raise error if line is NULL");
    cr_assert((lexer(NULL)) == -1));
    (void)header_name;
    (void)header_suite;
}