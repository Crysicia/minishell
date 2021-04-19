/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/15 16:44:08 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	(void)argc;
	(void)argv;
	if (!init_globals(envp))
		return (1);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		print_prompt();
		get_command(envp);
		sleep(0);
	}
	return (0);
}
