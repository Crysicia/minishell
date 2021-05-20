/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/06 17:20:22 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	write(1, "Minishell>", 10);
}

int	main(int argc, char *argv[], char *envp[])
{
	while (1)
	{
		print_prompt();
		get_command(envp);
		sleep(0);
	}
	(void)ret;
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
		return (-1);
	if (!init_globals(envp))
		return (1);
	run_minishell();
	(void)argv;
	(void)envp;
	return (0);
}
