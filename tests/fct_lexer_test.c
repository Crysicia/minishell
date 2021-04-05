#include <criterion/criterion.h>
#include "../includes/header.h"

Test(header_suite, header_test) {
    cr_assert((lexer(NULL)) == -1);
}