/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/12 16:24:31 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	init_globals(void)
{
	g_globals = malloc(sizeof(t_globals));
	if (!g_globals)
		return (false);
	g_globals->current_pid = 0;
	return (true);
}

void	handle_sigint(int signal)
{
	printf("Killing [%i]\n", g_globals->current_pid);
	if (g_globals->current_pid)
		kill(g_globals->current_pid, signal);
}

void	print_prompt(void)
{
	write(1, "Minishell>", 10);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (!init_globals())
		return (1);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		print_prompt();
		get_command(envp);
		sleep(0);
	}
	(void)argc;
	(void)argv;
	return (0);
}
