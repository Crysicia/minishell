#include <criterion/criterion.h>
#include <criterion/parameterized.h>
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

typedef struct  s_set_status_code_params {
    int ret;
    int code;
    bool from_builtin;
}               t_set_status_code_params;

ParameterizedTestParameters(exec_suite, set_status_code_test) {
    static  t_set_status_code_params set_status_code_params[] = {
        { .ret = 0, .code = 0, .from_builtin = true },
        { .ret = 50, .code = 50, .from_builtin = true },
        { .ret = 256, .code = 256, .from_builtin = true },
        { .ret = 1, .code = 256, .from_builtin = false },
        { .ret = 2, .code = 512, .from_builtin = false },
        { .ret = 4, .code = 1024, .from_builtin = false },
    };

    return cr_make_param_array(t_set_status_code_params, set_status_code_params, sizeof(set_status_code_params) / sizeof(t_set_status_code_params));
}

ParameterizedTest(t_set_status_code_params *set_status_code_params, exec_suite, set_status_code_test) {
    char *envp[] = { "SAMPLE=test" };
    int ret;

    init_globals(envp);
    
    ret = set_status_code(set_status_code_params->code, set_status_code_params->from_builtin);
    cr_expect_eq(ret, set_status_code_params->ret,
        "Expected set_status_code to return [%i], instead got [%i]",
        set_status_code_params->ret,
        ret
    );
    cr_expect_eq(g_globals->status, set_status_code_params->ret,
        "Expected set_status_code to set status to [%i], instead got [%i]",
        set_status_code_params->ret,
        g_globals->status
    );
    destroy_globals();
}
