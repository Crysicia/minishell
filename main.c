/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/15 11:42:32 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	destroy_globals(void)
{
	ft_lstclear(&g_globals->env, free);
	free(g_globals);
	return (false);
}

bool	init_globals(char *envp[])
{
	g_globals = malloc(sizeof(t_globals));
	if (!g_globals)
		return (false);
	g_globals->current_pid = 0;
	g_globals->env = array_to_list(envp);
	if (!g_globals->env)
		return (destroy_globals());
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
