/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/16 17:18:12 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


void reset_pids_array(void)
{
	free(g_globals->pids);
	g_globals->pids = NULL;
}

void	handle_sigint(int signal)
{
	printf("\n");
	if (g_globals->current_pid)
		kill(g_globals->current_pid, signal);
	rl_replace_line("", 0);
	rl_redisplay();
	if (!g_globals->current_pid)
		print_prompt();
}

void	handle_sigquit(int signal)
{
	char	*error;
	int		i = 0;

	error = "Quit (core dumped)\n";
	while (g_globals->pids && g_globals->pids[i])
	{
		kill(g_globals->pids[i], signal);
		i++;
	}
	if (g_globals->current_pid || g_globals->pids)
		write(2, error, ft_strlen(error));
	if (!g_globals->current_pid && !g_globals->pids)
		write(2, "\b\b  \b\b", 6);
	reset_pids_array();
	rl_replace_line("", 0);
	rl_redisplay();
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
