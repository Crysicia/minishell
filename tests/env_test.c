#include <criterion/criterion.h>
#include "../includes/header.h"
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

Test(env_suite, env_no_args_test) {
	char *input[] = { "BONJOUR=test", "LOL=", "USER=pcharton", "TEST=test", "NOPE", "ANOTHER=brickinthewall" };
	char *output[] = { "BONJOUR=test", "LOL=", "USER=pcharton", "TEST=test", "ANOTHER=brickinthewall" };
	init_globals(input);
	
	t_command command;
	command.args = ft_split("env", ' ');
	char *line = NULL;
	FILE *fp = NULL;
	int fd = 0;

	fp = freopen("env.test", "w", stdout);
	cr_expect(builtin_env(&command) == 0, "Expect builtin_env to return 0 without any argument");
	fclose(fp);
	fd = open("env.test", O_RDONLY);
	for (int i = 0; output[i]; i++)
	{
		get_next_line(fd, &line);
 	    cr_expect_str_eq(output[i], line,  "Expect printed strings to be the same, expected [%s], got [%s]", output[i], line);
	    cr_free(line);
	}
	close(fd);
	destroy_globals();
}
