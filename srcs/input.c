/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:31:36 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/26 12:33:45 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	gnl_loop_function(char *line)
{
	int		ret;
	char	*swap;
	char	*tmp;

	ret = 0;
	while (ret == 0)
	{
		ret = get_next_line(0, &tmp);
		swap = gnl_join(line, tmp);
		free(line);
		free(tmp);
		line = swap;
	}
	return (true);
}

char	*get_command(void)
{
	char	*line;
	int		ret;

	signal(SIGINT, handle_sigint);
	ret = get_next_line(0, &line);
	if (ret == -1 || line == NULL)
	{
		puts("gnl error");
		ft_exit_with_error_msg("Get_next_line returned -1.");
	}
	else if (!ft_strlen(line))
	{
		write(1, "\n", 1);
		exit (0);
	}
	else if (ret == 0)
		gnl_loop_function(line);
	return (line);
}

void	handle_sigint(int signal)
{
	printf("\n");
	if (g_globals->current_pid)
		kill(g_globals->current_pid, signal);
	// print_prompt();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "minishell: ", 11);
}

void	print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(1, "Minishell> ", 11);
}

void	skip_spaces(char **line)
{
	while (line && *line && (**line == ' ' || **line == '\t'))
		*line += 1;
}
