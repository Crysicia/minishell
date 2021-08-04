/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/08/04 14:35:43 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (!init_globals(envp))
		return (1);
	if (argc == 1)
		run_minishell();
	else
		return (-1);
	destroy_globals();
	return (0);
}
