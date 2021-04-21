/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:34:15 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/21 16:03:01 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <errno.h>
#include <string.h>

int	ft_putchar(int c)
{
	int	ret;

	ret = write(1, &c, 1);
	if (ret != 1)
	{
		printf("in %s line %d : error : %s\n",
			   __FILE__, __LINE__, strerror(errno));
		return (-1);
	}
	else
		return (0);
}

int main(void)
{
	int	ret;
	char *term;
	int column_count, line_count;
	term = getenv("TERM");

	ret = tgetent(NULL, term);
	if (ret == -1)
		printf("Database is not accessible.\n");
	else if (!ret)
		printf("Could not access database.\n");

	column_count = tgetnum("co");
	line_count = tgetnum("li");
	printf("col %d line %d\n", column_count, line_count);

	printf("%d\n", tgetflag("os"));
	char *clean = tgetstr("cl", NULL);
	tputs(clean, 0, ft_putchar);

	char *blink = tgetstr("mb", NULL);
	tputs(blink, 5, ft_putchar);
	puts("hello");
	puts("hoho");
}
