/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/08 17:31:13 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	g_current_pid;

void	handle_sigint(int signal)
{
	printf("Killing [%i]\n", g_current_pid);
	if (g_current_pid)
		kill(g_current_pid, signal);
}

void	print_prompt(void)
{
	write(1, "Minishell>", 10);
}

int	main(int argc, char *argv[], char *envp[])
{
	g_current_pid = 0;
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
