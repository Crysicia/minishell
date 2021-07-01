/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/01 16:16:58 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void handle_sigquit(int signal)
{
	if (g_globals->current_pid)
	{
		kill(g_globals->current_pid, signal);
		printf("Quit (core dumped)\n");
	}
	if (!g_globals->current_pid)
		write(1, "\b\b  \b\b", 6);
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
