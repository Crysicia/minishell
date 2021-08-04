/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/04 14:51:24 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_sigint(int signal)
{
	printf("\n");
	if (g_globals->pids && g_globals->pids[0])
		kill(g_globals->pids[0], signal);
	rl_replace_line("", 0);
	rl_redisplay();
	if (!g_globals->pids || !g_globals->pids[0])
		print_prompt();
}

void	handle_sigquit(int signal)
{
	char	*error;
	int		i;

	i = 0;
	error = "Quit (core dumped)\n";
	while (g_globals->pids && g_globals->pids[i])
	{
		kill(g_globals->pids[i], signal);
		i++;
	}
	if (!g_globals->pids || g_globals->pids[0] == 0)
		write(2, "\b\b  \b\b", 6);
	if (g_globals->pids)
	{
		write(2, error, ft_strlen(error));
		reset_pids_from_global();
	}
}

void	print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(1, "minishell: ", 11);
}

void	skip_spaces(char **line)
{
	while (line && *line && (**line == ' ' || **line == '\t'))
		*line += 1;
}

bool	ft_is_blank(char *str)
{
	while (*str)
	{
		if (!ft_strchr("\t\n\r\v\f", *str))
			return (false);
		str++;
	}
	return (true);
}
