/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/10 17:52:59 by pcharton         ###   ########.fr       */
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

void	execute_all_the_commands(t_list *list)
{
	t_list				*tmp;
	t_simple_command	*command;
	int					ret;

	ret = 0;
	tmp = list;
	while (tmp && (ret != -1))
	{
		command = tmp->content;
		if (command->type == simple_command)
		{
			ret = evaluate_token(&command->words);
		}
		else
			puts("pipeline is not implemented");
		tmp = tmp->next;
	}
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
		input_list = parser_loop(input_str);
		execute_all_the_commands(input_list);
	}
	(void)argv;
	return (0);
}
