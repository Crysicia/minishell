#include <criterion/criterion.h>
#include "../includes/header.h"
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

Test(env_suite, env_no_args_test) {
	char *envp[] = { "BONJOUR=test", "USER=pcharton", "TEST=test", "ANOTHER=brickinthewall", NULL };
	init_globals(envp);
	
	t_command command;
	command.args = ft_split("env", ' ');
	char *line = NULL;
	FILE *fp = NULL;
	int fd = 0;

	fp = freopen("env.test", "w", stdout);
	cr_expect(builtin_env(&command) == 0, "Expect builtin_env to return 0 without any argument");
	fclose(fp);
	fd = open("env.test", O_RDONLY);
	for (int i = 0; i < 4; i++)
	{
		get_next_line(fd, &line);
 	    cr_expect_str_eq(envp[i], line,  "Expect printed strings to be the same, expected [%s], got [%s]", envp[i], line);
	    cr_free(line);
	}
	close(fd);
}
