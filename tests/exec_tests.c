#include <criterion/criterion.h>
#include "../includes/header.h"
#include <string.h>
#include <signal.h>
#include <fcntl.h>

/*
Test(exec_suite, find_exe_path_test)
{
    char *envp[] = { "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL };
    init_globals(envp);
    t_command command;
    FILE *fp = NULL;
    int fd = 0;
    char *line = NULL;
    char *arguments[] = { "ls", "-la", ".", NULL };

    fp = freopen("exec.test", "w", stdout);
    system("which ls");
    fclose(fp);
    fd = open("exec.test", O_RDONLY);
    get_next_line(fd, &line);

    cr_expect(find_exe_path(arguments[0]) == 0, "Expect find_exe_path to find the path for ls");
    cr_expect(strcmp(command.executable, line) == 0, "Expect ls path to be %s", line);
    cr_free(command.executable);
    cr_free(line);
    close(fd);
}
*/
