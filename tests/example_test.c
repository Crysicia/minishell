#include <criterion/criterion.h>
#include "../includes/example.h"

Test(example_suite, example_test) {
    cr_expect(ft_max(1, 42) == 42, "Expect ft_max to return the biggest integer");
}
