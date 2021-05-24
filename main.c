/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/20 21:34:32 by lpassera         ###   ########.fr       */
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

int	evaluation_pass(t_list *list)
{
	t_list	*tmp;
	t_block	*ptr;

	tmp = list;
	while (tmp)
	{
		ptr = list->content;
		if (ptr->id == simple_command)
			flag_simple_command(ptr->kind.cmd);
		tmp = tmp->next;
	}
	return (0);
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
		if (ptr->id == simple_command || ptr->id == only_redirections)
			ret = execute_single_command(ptr->kind.cmd);
		else if (ptr->id == pipeline)
			ret = execute_pipeline(ptr->kind.pipe);
		else
		{
			printf("Shitty case (Nothing personal :3)\n");
			break ;
		}
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
		input_str = get_command();
		input_list = parser_loop(input_str);
		ret = evaluation_pass(input_list);
		ret = execute_all_the_commands(input_list);
		if (ret == -1)
		{
			puts("one command failed during execution");
			break ;
		}
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
	destroy_globals();
	return (0);
}
