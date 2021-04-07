#include <criterion/criterion.h>
#include "../includes/header.h"
#include <string.h>

Test(exec_suite, find_exe_path_test)
{
    t_command command;

    command.executable = NULL;
    command.args = malloc(4 * sizeof(char *));
    command.args[0] = strdup("ls");
    command.args[1] = strdup("-la");
    command.args[2] = strdup(".");
    command.args[3] = NULL;
    cr_expect(find_exe_path(&command) == 0, "Expect find_exe_path to find the path for ls");
    cr_log_warn("Executable path: %s", command.executable);
    cr_expect(strcmp(command.executable, "/bin/ls") == 0, "Expect ls path to be /bin/ls");
    cr_free(command.executable);
}
