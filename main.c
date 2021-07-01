/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/01 18:41:27 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	ft_is_blank(char *str)
{
	while (*str)
	{
		if (!ft_strchr("\t\n\r\v\f", *str))
			return (false);
		str++;
	}
	return (true);
}

void	run_minishell(void)
{
	t_list	*input_list;
	char	*input_str;
	int		ret;

	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		input_str = readline("minishell: ");
		if (!input_str)
			ft_exit();
		if (!ft_is_blank(input_str))
			add_history(input_str);
		input_list = parser_loop(input_str);
		if (!check_syntax_error(input_list))
		{
			ret = evaluation_pass(input_list);
			if (!ret)
				execute_all_the_commands(input_list);
		}
		ft_lstclear(&input_list, free_block);
		free(input_str);
	}
}

void	execute_all_the_commands(t_list *list)
{
	t_list		*tmp;
	t_block		*ptr;
	int			ret;

	ret = 0;
	tmp = list;
	while (tmp && (ret != -1))
	{
		ptr = tmp->content;
		if ((ptr->id == simple_command) || (ptr->id == only_redirections))
		{
			print_simple_command_node(ptr->kind.cmd);
			ret = execute_single_command(ptr->kind.cmd);
		}
		else if (ptr->id == pipeline)
		{
			print_pipeline(ptr->kind.pipe);
			ret = piping_loop(ptr->kind.pipe);
		}
		tmp = tmp->next;
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
