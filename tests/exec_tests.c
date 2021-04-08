#include <criterion/criterion.h>
#include "../includes/header.h"
#include <string.h>
#include <fcntl.h>

char    *aget_full_path(char *path, char *executable)
{
    char    current_path[PATH_MAX];

    ft_bzero(current_path, PATH_MAX);
    ft_strlcpy(current_path, path, ft_strlen(path) + 1);
    ft_strlcat(current_path, "/", PATH_MAX);
    ft_strlcat(current_path, executable, PATH_MAX);
    return (ft_strdup(current_path));
}

Test(exec_suite, find_exe_path_test)
{
    t_command command;
    FILE *fp = NULL;
    int fd = 0;
    char *line = NULL;

    command.args = malloc(4 * sizeof(char *));
    command.args[0] = strdup("ls");
    command.args[1] = strdup("-la");
    command.args[2] = strdup(".");
    command.args[3] = NULL;

    fp = freopen("exec.test", "w", stdout);
    system("which ls");
    fclose(fp);
    fd = open("exec.test", O_RDONLY);
    get_next_line(fd, &line);

    cr_log_info("DON'T REMOVE THIS COMMENT, IT MAKES THE NEXT TEST WORK AUTOMAGICALLY");
    cr_expect(find_exe_path(&command) == 0, "Expect find_exe_path to find the path for ls");
    cr_expect(strcmp(command.executable, line) == 0, "Expect ls path to be %s", line);
    cr_log_warn("Exec: %s", command.executable);
    cr_free(command.executable);
    cr_free(line);
}
