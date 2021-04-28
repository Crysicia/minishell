/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:34:15 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/26 12:07:08 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <termcap.h>
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

int	ft_putstr(char *str)
{
	write(1, str, strlen(str));
	return (0);
}

int	main(void)
{
	int		ret;
	char	*term;
	int		column_count;
	int		line_count;
	char	*clean;

	term = getenv("TERM");
	ret = tgetent(NULL, term);
	if (ret == -1)
		printf("Database is not accessible.\n");
	else if (ret == 0)
		printf("Could not access database.\n");
	column_count = tgetnum("co");
	line_count = tgetnum("li");
	clean = tgetstr("cl", NULL);
	tputs(clean, 0, ft_putchar);
	tputs(enter_bold_mode, 1, ft_putchar);
	tputs(erase_chars, 1, ft_putchar);
}
