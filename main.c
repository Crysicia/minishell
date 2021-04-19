/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/19 14:40:04 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	write(1, "Minishell>", 10);
}

void	handle_sigint(int signal)
{
//	printf("Killing [%i]\n", g_globals->current_pid);
	printf("\n");
	if (g_globals->current_pid)
		kill(g_globals->current_pid, signal);
	print_prompt();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*input_list;
	char	*input_str;

	if (argc != 1)
		return (-1);
	if (!init_globals(envp))
		return (1);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		print_prompt();
		input_str = get_command();
		input_list = command_parse(input_str);
//		lexer(input_str, envp);
		sleep(0);
	}
	(void)argv;
	return (0);
}
