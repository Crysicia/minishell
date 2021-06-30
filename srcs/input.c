/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/06/11 20:28:00 by pcharton         ###   ########.fr       */
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
