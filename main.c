/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/19 11:54:31 by lpassera         ###   ########.fr       */
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

int	execute_all_the_commands(t_list *list)
{
	t_list		*tmp;
	t_block		*ptr;
	int			ret;

	ret = 0;
	tmp = list;
	while (tmp && (ret != -1))
	{
		ptr = tmp->content;
		if (ptr->id == simple_command)
		{
			ret = execute_single_command(ptr->kind.cmd);
		}
		else
			puts("pipeline is not implemented");
		tmp = tmp->next;
	}
	return (0);
}

void run_minishell(void)
{
	t_list	*input_list;
	char	*input_str;
	int		ret;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		print_prompt();
		// test_redirections();
		input_str = get_command();
		input_list = parser_loop(input_str);
		print_command_list(input_list);
		ret = execute_all_the_commands(input_list);
		ft_lstclear(&input_list, free_block);
		free(input_str);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
		return (-1);
	if (!init_globals(envp))
		return (1);
	run_minishell();
	(void)argv;
	return (0);
}
