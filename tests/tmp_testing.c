#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char buffer[] = "echo \"123\"";
	int wr, fd;

	fd = open("tmp_test.truc", O_CREAT|O_WRONLY|O_TRUNC);
	wr = write(fd, buffer, strlen(buffer));
	if (wr == strlen(buffer))
		puts("all is ok");
	close(fd);
	char *ptr = buffer;
	while (*ptr)
	{
		printf("[%c]", *ptr);
		ptr++;
	}
	puts("");
	return (0);
}