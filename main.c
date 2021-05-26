/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/25 17:00:53 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	write(1, "Minishell> ", 11);
}

void	handle_sigint(int signal)
{
	printf("\n");
	if (g_globals->current_pid)
		kill(g_globals->current_pid, signal);
	print_prompt();
}

void	run_minishell(void)
{
	t_list	*input_list;
	char	*input_str;
	int		ret;

	(void)ret;
	signal(SIGINT, handle_sigint);
	while (1)
	{
		printf("-------------------------------\n---------- MAIN LOOP ----------\n-------------------------------\n");
		print_prompt();
		input_str = get_command();
		input_list = parser_loop(input_str);
		if (!check_syntax_error(input_list))
		{
			ret = evaluation_pass(input_list);
			if (!ret)
			{
				ret = execute_all_the_commands(input_list);
				add_to_history(input_str);
			}
		}
		ft_lstclear(&input_list, free_block);
		free(input_str);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (!init_globals(envp))
		return (1);
	if (argc == 1)
		run_minishell();
	else if ((argc == 3) && check_bash_c_option(argv[1]))
		bash_c_option(argv[2]);
	else
		return (-1);
	
	destroy_globals();
	return (0);
}
